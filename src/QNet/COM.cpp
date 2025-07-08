#include "COM.h"
#include <sys/neutrino.h>
#include <chrono>
#include <iostream>

COM::COM(I_Receiver *server, const char *clientSendName,
         I_Receiver *dispatcherRec, I_Sender *dispatcherSen)
    : _server(server), _clientSendName(clientSendName), _client(nullptr),
      _dispatcherRec(dispatcherRec), _dispatcherSen(dispatcherSen),
      lastHeartbeat(std::chrono::steady_clock::now()),
      running(false)
{
}

COM::~COM()
{
    stop();
}
void COM::start() {
    if (running) return;

    running = true;
    
    auto set_priority = [](int priority) {
        struct sched_param param;
        param.sched_priority = priority;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    };

    // Dispatcher (Highest Priority - Handles Critical Events)
    dispatcherThread = std::thread([this, set_priority]{
        set_priority(10);  // Highest
        runDispatcher();
    });

    // Client (Medium Priority - Sends Messages)
    clientThread = std::thread([this, set_priority]{
        set_priority(10);
        runClient();
    });

    // Server (Lowest Priority - Background Tasks)
    serverThread = std::thread([this, set_priority]{
        set_priority(5);
        runServer();
    });
}

void COM::stop()
{
    if (!running)
        return;

    running = false;
    queueCV.notify_all();
    //dispatcherSen->send_event((int8_t)Topic::WAKE_UP,0);

    if (clientThread.joinable())
        clientThread.join();
    if (serverThread.joinable())
        serverThread.join();
    if (dispatcherThread.joinable())
        dispatcherThread.join();
}

void COM::runDispatcher()
{
    while (running)
    {
        _pulse dispatcherMsg;
        if (_dispatcherRec->receive_event(&dispatcherMsg) == 0)
        {
            Topic originalTopic = static_cast<Topic>(dispatcherMsg.code);
            int originalValue = dispatcherMsg.value.sival_int;

            {
                std::lock_guard<std::mutex> lock(queueMutex);
                switch (originalTopic)
                {
                case Topic::INTERRUPT:
                    handleInterruptTopic(originalValue, dispatcherMsg);
                    break;
                case Topic::INTERNAL:
                    handleInternalTopic(originalValue, dispatcherMsg);
                    break;
                case Topic::COM:
                    handleComTopic(originalValue, dispatcherMsg);
                    break;
                case Topic::REM_CON:
                    handleRemConTopic(originalValue, dispatcherMsg);
                    break;
                case Topic::ID:
                  lowPriorityQueue.push_back(dispatcherMsg);
                  break;
                default:
                    break; // No conversion needed
                }
            }
            queueCV.notify_one(); // Wake up client thread
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Small yield
    }
}

void COM::runClient() {
  const int RETRY_DELAY_MS = 1000;
  while (running) {
    while (!_client || _client->getcoid() == -1) {
      std::lock_guard<std::mutex> lock(_clientMutex);
      try {
        _client = make_unique<Thread_COM::Sender>(_clientSendName);
        if (_client->getcoid() >= 0) {
          COUT("Connection established successfully");
          break;
        }
      } catch (...) {
        std::cerr << "Error creating Sender in run client com.cpp" << std::endl;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS));
      continue;
    } 
    if (_client && _client->getcoid() != -1) {
      checkQueues();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }
}
void COM::checkQueues() {
    const size_t MAX_BATCH = 10;
    
    while (running) {
        // Local batch containers
        std::deque<_pulse> highPrioBatch;
        std::deque<_pulse> lowPrioBatch;
        
        { // Locked scope
            std::unique_lock<std::mutex> lock(queueMutex);
            
            // Move items to local batches
            auto move_batch = [](std::deque<_pulse>& src, std::deque<_pulse>& dest, size_t max) {
                auto end = src.size() > max ? src.begin() + max : src.end();
                dest.insert(dest.end(), std::make_move_iterator(src.begin()), 
                                    std::make_move_iterator(end));
                src.erase(src.begin(), end);
            };
            
            if (!highPriorityQueue.empty()) {
                move_batch(highPriorityQueue, highPrioBatch, MAX_BATCH);
            } else if (!lowPriorityQueue.empty()) {
                move_batch(lowPriorityQueue, lowPrioBatch, MAX_BATCH);
            } else {
                break; // Both queues empty
            }
        } // Lock released
        
        // Process high priority first
        for (auto& msg : highPrioBatch) {
            if (sendToServer(msg, (int)EventPriority::FIRST_PRIO) == -1) {
                std::lock_guard<std::mutex> lock(queueMutex);
                highPriorityQueue.push_front(std::move(msg));
            }
        }
        
        // Then process low priority
        for (auto& msg : lowPrioBatch) {
            if (sendToServer(msg) == -1) {
                std::lock_guard<std::mutex> lock(queueMutex);
                lowPriorityQueue.push_front(std::move(msg));
            }
        }
        
        // Cooperative yield
        std::this_thread::yield();
    }
    
    // Only send heartbeat when truly idle
    if (highPriorityQueue.empty() && lowPriorityQueue.empty()) {
        sendHeartbeat();
    }
}

void COM::sendHeartbeat()
{

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - lastHeartbeat);

    if (elapsed.count() >= HEARTBEAT_INTERVAL)
    {
        std::lock_guard<std::mutex> lock(_clientMutex);
        if (_client->getcoid() != -1)
        {
            _client->send_event((int8_t)Topic::COM, (int)COM_Enum::HEARTBEAT);
        }
        updateHeartbeat();
    }
}

int COM::sendToServer(const _pulse &msg, int priority)
{
  int send_event_status = 0;
  std::lock_guard<std::mutex> lock(_clientMutex);
    if (_client)
    {
        send_event_status = _client->send_event_com((int8_t)msg.code, (int)msg.value.sival_int, (int)priority);
    }
    updateHeartbeat();
    return send_event_status;
}

// Server side implementation
void COM::runServer()
{
    COUT("COM server started.");
    bool disconnected = true;
    while (running)
    {
        struct _pulse event;
        struct _msg_info info; 
        struct sigevent sigev;
        uint64_t timeout_nsec = 3 * 1000000000ULL; 
        sigev.sigev_notify = SIGEV_UNBLOCK;
        TimerTimeout(CLOCK_MONOTONIC,
                     _NTO_TIMEOUT_RECEIVE,
                     &sigev,
                     &timeout_nsec,
                     NULL);
        int rcvid = MsgReceive(_server->getchid(),
                               &event,
                               sizeof(event),
                               &info);

        if (rcvid == 0)
        {
            if (disconnected)
            {
                disconnected = false;

                // Send COM_CONNECTED notification
                _pulse reconnectEvent;
                reconnectEvent.code = static_cast<int8_t>(Topic::COM);
                reconnectEvent.value.sival_int = static_cast<int>(COM_Enum::COM_CONNECTED);
                sendToDispatcher(reconnectEvent, static_cast<int>(EventPriority::FIRST_PRIO));

                // Prepare status events
                _pulse rampEvent;
                rampEvent.code = static_cast<int8_t>(Topic::COM);
                rampEvent.value.sival_int = rampfull ? static_cast<int>(COM_Enum::RAMP_FULL)
                                                     : static_cast<int>(COM_Enum::RAMP_NOT_FULL);
                _pulse mqttEvent;
                mqttEvent.code = static_cast<int8_t>(Topic::COM);
                mqttEvent.value.sival_int = mqttConnected ? static_cast<int>(COM_Enum::COM_MQTT_CONNECTED)
                                                          : static_cast<int>(COM_Enum::COM_MQTT_DISCONNECTED);
                {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    lowPriorityQueue.push_front(rampEvent);
                    lowPriorityQueue.push_front(mqttEvent);
                }
            }

            if ((_PULSE_CODE_MINAVAIL <= event.code) && (event.code <= _PULSE_CODE_MAXAVAIL))
            {
                updateHeartbeat();
                processMessage(event);
            }
            else
            {
                handle_QNX_pulse(&event, rcvid);
                continue;
            }
        }
        else if (rcvid == -1)
        {
            if (errno == ETIMEDOUT)
            {
                {
                    std::lock_guard<std::mutex> lock(_clientMutex);
                    _client.reset();
                }
                // Timeout occurred
                disconnected = true;
                updateHeartbeat();

                _pulse timeoutEvent;
                int8_t comCode = (int8_t)Topic::COM;
                int value = (int)COM_Enum::TIMEOUT_COM;

                timeoutEvent.code = comCode;
                timeoutEvent.value.sival_int = value;
                COUT("Sending Timeout Notification; COM_Server");
                sendToDispatcher(timeoutEvent, (int)EventPriority::FIRST_PRIO);
            }
        }
        if ((_IO_BASE <= event.type) && (event.type <= _IO_MAX))
        {
            handle_QNX_IO_msg(&event, rcvid);
            continue;
        }
    }
}

void COM::handle_QNX_pulse(_pulse *msg, int rcvid)
{
    switch (msg->code)
    {
    case _PULSE_CODE_DISCONNECT:
        printf("PULSE_CODE_DISCONNECT\n");
        ConnectDetach(msg->scoid);
        break;
    case _PULSE_CODE_UNBLOCK:
        printf("received _PULSE_CODE_UNBLOCK\n");
        break;
    case _PULSE_CODE_COIDDEATH:
        printf("Received _PULSE_CODE_COIDDEATH\n")
        ConnectDetach(msg->scoid);
        break;
    default:
        /* A pulse sent by the kernel like
         * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
         * from the kernel? */
        printf(" received some other QNX pulse msg code: %d.\n", msg->code);
        break;
    }
}
void COM::handle_QNX_IO_msg(_pulse *msg, int rcvid)
{
    _pulse timeoutEvent;
    int8_t comCode = (int8_t)Topic::COM;
    int value = (int)COM_Enum::TIMEOUT_COM;
    switch (msg->code)
    {
    case _PULSE_CODE_DISCONNECT:
        printf(" _PULSE_CODE_DISCONNECT\n");
        /* A client disconnected all its connections (called
         * name_close() for each name_open() of our name) or
         * terminated. */

        timeoutEvent.code = comCode;
        timeoutEvent.value.sival_int = value;
        COUT("Sending Timeout Notification");
        sendToDispatcher(timeoutEvent); // Andere Maschine disconeccted -> Timeout
        ConnectDetach(msg->scoid);
        break;
    case _PULSE_CODE_UNBLOCK:
        printf(" received _PULSE_CODE_UNBLOCK\n");
        /* REPLY blocked client wants to unblock (was hit by
         * a signal or timed out). It's up to you if you
         * reply now or later. */
        break;
    case 12:
        printf(" Sending EOK, connect\n");
        MsgReply(rcvid, EOK, NULL, 0);
        break;
    default:
        /* A pulse sent by the kernel like
         * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
         * from the kernel? */
        printf(" received some other QNX pulse msg code: %d\n", msg->code);
        break;
    }
}

void COM::processMessage(const _pulse &msg)
{
    if (msg.code == ((int)Topic::COM))
    { 
        if (msg.value.sival_int == ((int)COM_Enum::BUTTON_ESTOP_PRESSED))
        {
            sendToDispatcher(msg, (int)EventPriority::FIRST_PRIO);
        }
        else if (msg.value.sival_int != (((int)COM_Enum::TIMEOUT_COM) || ((int)COM_Enum::HEARTBEAT)))
        {
            sendToDispatcher(msg);
        }
    }
    else if (msg.code == (int) Topic::ID)
    {
      sendToDispatcher(msg);
    }
    else
    {
        printf("Received non COM Topic & non id Topic from other machine: Event Code: %d, Event Value: %d\n", msg.code, msg.value.sival_int);
    }
}

void COM::sendToDispatcher(const _pulse &msg, int priority)
{
    _dispatcherSen->send_event(msg.code, (int)msg.value.sival_int, priority);
}

void COM::updateHeartbeat()
{
    lastHeartbeat = std::chrono::steady_clock::now();
}

void COM::handleInterruptTopic(int originalValue, _pulse &dispatcherMsg)
{
    InterruptEnum interruptEvent = static_cast<InterruptEnum>(originalValue);
    switch (interruptEvent)
    {
    case InterruptEnum::BUTTON_ESTOP_PRESSED:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::BUTTON_ESTOP_PRESSED);
        highPriorityQueue.push_back(dispatcherMsg);
        break;
    case InterruptEnum::BUTTON_ESTOP_RELEASED:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::BUTTON_ESTOP_RELEASED);
        highPriorityQueue.push_back(dispatcherMsg);
        break;
    case InterruptEnum::BUTTON_RESET_PRESSED:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::BUTTON_RESET_PRESSED);
        highPriorityQueue.push_back(dispatcherMsg);
        break; 
    default:
        break;
    }
}

void COM::handleInternalTopic(int originalValue, _pulse &dispatcherMsg)
{
    Internal_Enum internalEvent = static_cast<Internal_Enum>(originalValue);
    switch (internalEvent)
    {
    case Internal_Enum::RESET_TO_FLAT:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RESET_TO_FLAT);
        lowPriorityQueue.push_back(dispatcherMsg);
        break;
    case Internal_Enum::RESET_TO_TALL:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RESET_TO_TALL);
        lowPriorityQueue.push_back(dispatcherMsg);
        break;
    case Internal_Enum::RESET_TO_TALL_W_METAL:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RESET_TO_TALL_W_METAL);
        lowPriorityQueue.push_back(dispatcherMsg);
        break;
    case Internal_Enum::RAMP_NOT_FULL:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RAMP_NOT_FULL);
        lowPriorityQueue.push_back(dispatcherMsg);
        rampfull = false;
        break;
    case Internal_Enum::RAMP_FULL:
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::RAMP_FULL);
        lowPriorityQueue.push_back(dispatcherMsg);
        rampfull = true;
        break;
    default:
        break;
    }
}

void COM::handleComTopic(int originalValue, _pulse &dispatcherMsg)
{
    if (originalValue == static_cast<int>(COM_Enum::TIMEOUT_COM) ||
        originalValue == static_cast<int>(COM_Enum::COM_CONNECTED) ||
        originalValue == static_cast<int>(COM_Enum::HEARTBEAT) ||
        originalValue == static_cast<int>(COM_Enum::RAMP_FULL) ||
        originalValue == static_cast<int>(COM_Enum::RAMP_NOT_FULL) ||
        originalValue == static_cast<int>(COM_Enum::RESET_TO_FLAT) ||
        originalValue == static_cast<int>(COM_Enum::RESET_TO_TALL) ||
        originalValue == static_cast<int>(COM_Enum::RESET_TO_TALL_W_METAL) ||
        originalValue == static_cast<int>(COM_Enum::BUTTON_ESTOP_PRESSED) ||
        originalValue == static_cast<int>(COM_Enum::BUTTON_ESTOP_RELEASED) ||
        originalValue == static_cast<int>(COM_Enum::BUTTON_RESET_PRESSED))
    {
        return;
    }
    if (FBM == 1)
    {
        if ((originalValue == static_cast<int>(COM_Enum::FBM_2_BUSY) ||
             originalValue == static_cast<int>(COM_Enum::FBM_2_READY)) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_FAILED) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_DONE))
            return;
    }
    if (FBM == 2)
    {
        if (originalValue == static_cast<int>(COM_Enum::TRANSFER_START_TALL) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_START_FLAT) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_START_OTHER) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_START_TALL_W_METAL) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_START_TALL_SORT_OUT) ||
            originalValue == static_cast<int>(COM_Enum::TRANSFER_START_FLAT_SORT_OUT) || 
            originalValue == static_cast<int>(COM_Enum::TRANSFER_START_TALL_W_METAL_SORT_OUT) ||
            originalValue == static_cast<int>(COM_Enum::REQUEST_TRANSFER)||
            originalValue == static_cast<int>(COM_Enum::REQUEST_TRANSFER_SORT) )
            return;
    }
    lowPriorityQueue.push_back(dispatcherMsg);
}

void COM::handleRemConTopic(int originalValue, _pulse &dispatcherMsg)
{
    switch (originalValue)
    {
    case static_cast<int>(RemoteControlEnum::MQTT_CONNECTED):
        mqttConnected = true;
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::COM_MQTT_CONNECTED);
        lowPriorityQueue.push_back(dispatcherMsg);
 
        break;
    case static_cast<int>(RemoteControlEnum::MQTT_DISCONNECTED):
        mqttConnected = false;
        dispatcherMsg.code = static_cast<int>(Topic::COM);
        dispatcherMsg.value.sival_int = static_cast<int>(COM_Enum::COM_MQTT_DISCONNECTED);
        lowPriorityQueue.push_back(dispatcherMsg);
        break;
    default:
        break;
    }
}
