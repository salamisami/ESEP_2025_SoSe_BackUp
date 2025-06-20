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
}

void COM::stop() {
    if (!running) return;
    
    running = false;
    queueCV.notify_all();
    
    if (clientThread.joinable()) clientThread.join();
    if (serverThread.joinable()) serverThread.join();
}

void COM::addMessage(const _pulse& msg) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        
        if (msg.code == ESTOP_CODE) {
            highPriorityQueue.push_back(msg);
        } else {
            lowPriorityQueue.push_back(msg);
        }
    }
    queueCV.notify_one();
}

void COM::runClient() {
    COUT("COM Client started.");
    const int MAX_RETRIES = 5;
    const int RETRY_DELAY_MS = 1000;
    const int HEARTBEAT_INTERVAL_MS = 5000;
    const int DISPATCHER_POLL_INTERVAL_MS = 10; // Check dispatcher every 100ms

    auto lastHeartbeatTime = std::chrono::steady_clock::now();
    auto lastDispatcherCheckTime = std::chrono::steady_clock::now();
    int retry_count = 0;

    while (running) {
        // 1. Check connection status and establish if needed
        if (!_client || _client->getcoid() == -1) {
            if (retry_count < MAX_RETRIES) {
                try {
                    _client = make_unique<Thread_COM::Sender>(_clientSendName);
                    if (_client->getcoid() >= 0) {
                        retry_count = 0; // Reset on success
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
                // Max retries reached, wait before trying again
                std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS * 2));
                continue;
            }
        }

        // 2. Check for dispatcher messages periodically
        auto now = std::chrono::steady_clock::now();
        auto elapsedDispatcherCheck = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - lastDispatcherCheckTime);

        if (elapsedDispatcherCheck.count() >= DISPATCHER_POLL_INTERVAL_MS) {
            _pulse dispatcherMsg;
            if (_dispatcherRec->receive_event(&dispatcherMsg) == 1) { // Non-blocking check
                if (dispatcherMsg.code == static_cast<int8_t>(Topic::COM)) {
                    // Handle COM topic message from dispatcher
                    COUT("Received COM message from dispatcher");
                    addMessage(dispatcherMsg);
                }
                // Other dispatcher messages can be handled here if needed
            }
            lastDispatcherCheckTime = now;
        }

        // 3. Process outgoing queues
        checkQueues();
        
        // 4. Send heartbeat if needed
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
    
    // Process ALL high priority messages first
    while (!highPriorityQueue.empty()) {
        auto msg = highPriorityQueue.front();
        highPriorityQueue.pop_front();
        lock.unlock();
        sendToServer(msg, (int) EventPriority::FIRST_PRIO );
        lock.lock();
    }

    // Process low priority only when higher queues are empty
    while (!lowPriorityQueue.empty()) {
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
        int result = _server->receive_event(&event);
        
        if (result == 1) {  // QNX pulse received
            updateHeartbeat();
            processMessage(event);
        }
        else if (result == -1) {
            if (errno == ETIMEDOUT) {
                updateHeartbeat();
                
                // Send timeout notification to dispatcher
                _pulse timeoutEvent;
                timeoutEvent.code = TIMEOUT_CODE;
                timeoutEvent.value.sival_int = 0;
                COUT("Sending Timeout");
                sendToDispatcher(timeoutEvent);
            }
            // Handle other errors if needed
        }
    }
}

void COM::processMessage(const _pulse& msg) {
    // Process ES messages immediately
    if (msg.code == ESTOP_CODE) {
        sendToDispatcher(msg, (int) EventPriority::FIRST_PRIO);
    } 
    // Process other messages
    else {
        // Add your message processing logic here
        // ...
        
        // Forward to dispatcher if needed
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
