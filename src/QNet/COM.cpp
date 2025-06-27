#include "COM.h"
#include <sys/neutrino.h>
#include <chrono>
#include <iostream>



COM::COM(I_Receiver* server, const char* clientSendName,
         I_Receiver* dispatcherRec, I_Sender* dispatcherSen)
    : _server(server), _clientSendName(clientSendName), _client(nullptr),
      _dispatcherRec(dispatcherRec), _dispatcherSen(dispatcherSen),
      lastHeartbeat(std::chrono::steady_clock::now()),
      running(false) {}

COM::~COM() {
    stop();
}
void COM::start() {
    COUT("COM started.");
    if (running) return;
    
    running = true;
    clientThread = std::thread(&COM::runClient, this);
    serverThread = std::thread(&COM::runServer, this);
    dispatcherThread = std::thread(&COM::runDispatcher, this); // New dispatcher thread
}

void COM::stop() {
    if (!running) return;
    
    running = false;
    queueCV.notify_all();
    
    if (clientThread.joinable()) clientThread.join();
    if (serverThread.joinable()) serverThread.join();
    if (dispatcherThread.joinable()) dispatcherThread.join(); // Clean up dispatcher thread
}

void COM::runDispatcher() {
    COUT("Dispatcher handler started.");
    while (running) {
        _pulse dispatcherMsg;
        if (_dispatcherRec->receive_event(&dispatcherMsg) == 0) {
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                // TODO: MESSAGES TO BE PASSED TO OTHER MACHINE
                // Check if the message is of type Topic::INTERRUPT
                if (dispatcherMsg.code == static_cast<int>(Topic::INTERRUPT)) {
                    dispatcherMsg.code = static_cast<int>(Topic::COM);
                    // Check if the interrupt is either BUTTON_ESTOP_PRESSED or BUTTON_ESTOP_RELEASED
                    if (dispatcherMsg.value.sival_int == static_cast<int>(InterruptEnum::BUTTON_ESTOP_PRESSED) ||
                        dispatcherMsg.value.sival_int == static_cast<int>(InterruptEnum::BUTTON_ESTOP_RELEASED)) {
                        highPriorityQueue.push_back(dispatcherMsg);
                        COUT("Received EStop from dispatcher (high priority)");
                    } else {
                        lowPriorityQueue.push_back(dispatcherMsg);

                    }
                } else {
                    // For non-interrupt messages, add to low priority queue
                    lowPriorityQueue.push_back(dispatcherMsg);
                    COUT("Received message from dispatcher");
                }
            }
            queueCV.notify_one(); // Wake up client thread if it's waiting
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Small yield
    }
}

void COM::runClient() {
    COUT("COM Client started.");
    const int MAX_RETRIES = 50;
    const int RETRY_DELAY_MS = 1000;
    const int HEARTBEAT_INTERVAL_MS = 2000;

    auto lastHeartbeatTime = std::chrono::steady_clock::now();
    int retry_count = 0;

    while (running) {
        // Connection management (unchanged)
        if (!_client || _client->getcoid() == -1) {
            if (retry_count < MAX_RETRIES) {
                try {
                    _client = make_unique<Thread_COM::Sender>(_clientSendName);
                    if (_client->getcoid() >= 0) {
                        retry_count = 0;
                        COUT("Connection established successfully");
                    } else {
                        retry_count++;
                    }
                } catch (...) {
                    retry_count++;
                    std::cerr << "Error creating Sender in run client com.cpp" << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS));
                continue;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS * 2));
            }
        }
        if (_client->getcoid()==-1){
        	_pulse timeoutEvent;
        	int8_t comCode = (int8_t) Topic::COM;
        	int value = (int) COM_Enum::TIMEOUT_COM;
        	timeoutEvent.code = comCode;
        	timeoutEvent.value.sival_int = value;
        	COUT("Sending Timeout Notification to dispatcher");
        	sendToDispatcher(timeoutEvent);
        }
        else {
            checkQueues();
        }
        retry_count=0;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void COM::checkQueues() {
    std::unique_lock<std::mutex> lock(queueMutex);
    
    // Send heartbeat if queues are empty
    if (highPriorityQueue.empty() &&
        lowPriorityQueue.empty()) {
        lock.unlock();
        sendHeartbeat();
        return;
    }

    while (!highPriorityQueue.empty()) {
    	COUT("Something in high prio received");
        auto msg = highPriorityQueue.front();
        highPriorityQueue.pop_front();
        lock.unlock();
        sendToServer(msg, (int) EventPriority::FIRST_PRIO );
        lock.lock();
    }

    // Process low priority only when higher queues are empty
    while (!lowPriorityQueue.empty()) {
    	COUT("Something in low prio");
        auto msg = lowPriorityQueue.front();
        lowPriorityQueue.pop_front();
        lock.unlock();
        sendToServer(msg);
        lock.lock();
    }
}

void COM::sendHeartbeat() {

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        now - lastHeartbeat);
    
    if (elapsed.count() >= HEARTBEAT_INTERVAL) {
    	if (_client->getcoid() != -1) {
    	    _client->send_event((int8_t) Topic::COM, (int) COM_Enum::HEARTBEAT);
    	}
        updateHeartbeat();
    }
}

void COM::sendToServer(const _pulse& msg, int priority) {
    _client->send_event((int8_t) msg.code, (int) msg.value.sival_int, (int) priority);
    updateHeartbeat();
}

// Server side implementation
void COM::runServer() {
	COUT("COM server started.");
    while (running) {
		struct _pulse event;
		struct _msg_info info;  // Message info structure
		struct sigevent sigev;
		uint64_t timeout_nsec = 5 * 1000000000ULL; // 5 seconds in nanoseconds

		// Setup timeout structure
		sigev.sigev_notify = SIGEV_UNBLOCK;

		// Arm the receive timeout
		TimerTimeout(CLOCK_MONOTONIC,
					_NTO_TIMEOUT_RECEIVE,
					&sigev,
					&timeout_nsec,
					NULL);

		// Perform the receive operation
		int rcvid = MsgReceive(_server->getchid(),
							  &event,
							  sizeof(event),
							  &info);
        
        if (rcvid == 0) {
        	COUT("RECEIVED MESSAGE FROM OTHER MACHINE");

        	if((_PULSE_CODE_MINAVAIL <= event.code) && (event.code <= _PULSE_CODE_MAXAVAIL)) {
                updateHeartbeat();
                processMessage(event);
        	        } else {
        	            handle_QNX_pulse(&event, rcvid);
        	            continue;
        	        }
        }
        else if (rcvid == -1) {
            if (errno == ETIMEDOUT) {
                // Timeout occurred
                updateHeartbeat();
                
                _pulse timeoutEvent;
                int8_t comCode = (int8_t) Topic::COM;
                int value = (int) COM_Enum::TIMEOUT_COM;

                timeoutEvent.code = comCode;
                timeoutEvent.value.sival_int = value;
                COUT("Sending Timeout Notification");
                sendToDispatcher(timeoutEvent);
            }
        }
			if((_IO_BASE <= event.type) && (event.type <= _IO_MAX)) {
				// Some QNX IO msg generated by gns was received
				handle_QNX_IO_msg(&event, rcvid);
				continue;
        }
    }
}

void COM::handle_QNX_pulse(_pulse* msg, int rcvid) {
    switch(msg->code) {
        case _PULSE_CODE_DISCONNECT:
            printf("PULSE_CODE_DISCONNECT\n");
            /* A client disconnected all its connections (called
            * name_close() for each name_open() of our name) or
            * terminated. */
            ConnectDetach(msg->scoid);
            break;
        case _PULSE_CODE_UNBLOCK:
            printf("received _PULSE_CODE_UNBLOCK\n");
            /* REPLY blocked client wants to unblock (was hit by
            * a signal or timed out). It's up to you if you
            * reply now or later. */
            break;
        default:
            /* A pulse sent by the kernel like
            * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
            * from the kernel? */
            printf(" received some other QNX pulse msg code: %d.\n", msg->code);
            break;
    }
}
void COM::handle_QNX_IO_msg(_pulse* msg, int rcvid) {
    switch(msg->code) {
        case _PULSE_CODE_DISCONNECT:
            printf(" _PULSE_CODE_DISCONNECT\n");
            /* A client disconnected all its connections (called
            * name_close() for each name_open() of our name) or
            * terminated. */
            _pulse timeoutEvent;
            int8_t comCode = (int8_t) Topic::COM;
            int value = (int) COM_Enum::TIMEOUT_COM;

            timeoutEvent.code = comCode;
            timeoutEvent.value.sival_int = value;
            COUT("Sending Timeout Notification");
            sendToDispatcher(timeoutEvent);  // Andere Maschine disconeccted -> Timeout
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


void COM::processMessage(const _pulse& msg) {
    // Process ES messages immediately Same priority goes to connection lost
    if (msg.value.sival_int == ((int) COM_Enum::BUTTON_ESTOP_PRESSED)) {
        sendToDispatcher(msg, (int) EventPriority::FIRST_PRIO);
        COUT("SENDING ESTOP TO DISPATCHER");
    } 
    else if (msg.value.sival_int != ((int) COM_Enum::TIMEOUT_COM)){
        // Add your message processing logic here
        sendToDispatcher(msg);
    }
}

void COM::sendToDispatcher(const _pulse& msg, int priority) {
    _dispatcherSen->send_event(msg.code, (int) msg.value.sival_int, priority);
}

void COM::updateHeartbeat() {
    lastHeartbeat = std::chrono::steady_clock::now();
}
