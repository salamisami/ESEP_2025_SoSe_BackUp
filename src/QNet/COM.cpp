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

// New dispatcher message handling thread
void COM::runDispatcher() {
    COUT("Dispatcher handler started.");
    while (running) {
        _pulse dispatcherMsg;
        if (_dispatcherRec->receive_event(&dispatcherMsg) == 0) {
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                if (dispatcherMsg.code == ((int) COM_Enum::BUTTON_ESTOP_PRESSED)) {
                    highPriorityQueue.push_back(dispatcherMsg);
                    COUT("Received EStop from dispatcher (high priority)");
                } else {
                    lowPriorityQueue.push_back(dispatcherMsg);
                    COUT("Received message from dispatcher");
                }
            }
            queueCV.notify_one(); // Wake up client thread if it's waiting
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Small yield
    }
}

// Simplified runClient (removed dispatcher checking)
void COM::runClient() {
    COUT("COM Client started.");
    const int MAX_RETRIES = 50;
    const int RETRY_DELAY_MS = 1000;
    const int HEARTBEAT_INTERVAL_MS = 5000;

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
                        std::cerr << "Connection attempt " << retry_count << " failed." << std::endl;
                    }
                } catch (...) {
                    retry_count++;
                    std::cerr << "Error creating Sender" << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS));
                continue;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS * 2));
                continue;
            }
        }

        // Process queues (unchanged)
        checkQueues();
        
        // Heartbeat logic (unchanged)
        auto now = std::chrono::steady_clock::now();
        auto elapsedHeartbeat = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastHeartbeatTime);
        if (elapsedHeartbeat.count() >= HEARTBEAT_INTERVAL_MS) {
            if (_client->getcoid() != -1) {
                _client->send_event(static_cast<int8_t>(Topic::COM), static_cast<int>(COM_Enum::HEARTBEAT));
                lastHeartbeatTime = now;
                COUT("Sent heartbeat");
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void COM::checkQueues() {
    std::unique_lock<std::mutex> lock(queueMutex);
    
    int8_t comCode = (int8_t) Topic::COM;
    int value = (int) COM_Enum::BUTTON_ESTOP_PRESSED;
    //_client-> send_event(comCode, value);

    // Process ALL high priority messages first
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

    // Send heartbeat if queues are empty
    if (highPriorityQueue.empty() &&
        lowPriorityQueue.empty()) {
        lock.unlock();
        sendHeartbeat();
    }
}

void COM::sendHeartbeat() {

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        now - lastHeartbeat);
    
    if (elapsed.count() >= HEARTBEAT_INTERVAL) {
    	const int MAX_RETRIES = 3;
    	int attempts = 0;

    	while (attempts < MAX_RETRIES) {
    	    if (_client->getcoid() == -1) {
    	        _client = make_unique<Thread_COM::Sender>(_clientSendName);
    	        attempts++;
    	        delay(10 * attempts);  // Exponential backoff
    	    } else {
    	        break;
    	    }
    	}

    	if (_client->getcoid() != -1) {
    	    _client->send_event((int8_t) Topic::COM, (int) COM_Enum::HEARTBEAT);
    	} else {
    	    // sendDispatcher disconnect
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
    _pulse event;
    
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
        
        if (rcvid > 0) {
            // Successfully received a pulse
            COUT("RECEIVED MESSAGE FROM OTHER MACHINE");
            updateHeartbeat();
            processMessage(event);
        }
        else if (rcvid == -1) {
            if (errno == ETIMEDOUT) {
                // Timeout occurred
                updateHeartbeat();
                
                _pulse timeoutEvent;
                int8_t comCode = (int8_t) Topic::COM;
                int value = (int) COM_Enum::TIMEOUT;

                timeoutEvent.code = comCode;
                timeoutEvent.value.sival_int = value;
                COUT("Sending Timeout Notification");
                sendToDispatcher(timeoutEvent);
            }
            else {
                // Other error occurred
                COUT("Error receiving pulse: " << strerror(errno));
            }
        }
    }
}

void COM::processMessage(const _pulse& msg) {
    // Process ES messages immediately Same priority goes to connection lost
    if (msg.code == ((int) COM_Enum::BUTTON_ESTOP_PRESSED)) {
        sendToDispatcher(msg, (int) EventPriority::FIRST_PRIO);
        COUT("SENDING ESTOP TO DISPATCHER");
    } 
    else {
        // Add your message processing logic here
        sendToDispatcher(msg);
    }
}

void COM::sendToDispatcher(const _pulse& msg, int priority) {
    _dispatcherSen->send_event(msg.code, (int) msg.value.sival_int, priority);
}

void COM::updateHeartbeat() {
	COUT("Updating Heartbeat");
    lastHeartbeat = std::chrono::steady_clock::now();
}
