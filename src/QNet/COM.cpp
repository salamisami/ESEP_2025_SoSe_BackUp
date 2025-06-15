#include "COM.h"
#include <sys/neutrino.h>
#include <chrono>
#include <iostream>

COM::COM(I_Receiver* server, I_Sender* client, 
         I_Receiver* dispatcherRec, I_Sender* dispatcherSen)
    : _server(server), _client(client),
      _dispatcherRec(dispatcherRec), _dispatcherSen(dispatcherSen),
      lastHeartbeat(std::chrono::steady_clock::now()),
      running(false) {}

COM::~COM() {
    stop();
}

void COM::start() {
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
        
        // Prioritize messages
        if (msg.code == ESTOP_CODE) {
            highPriorityQueue.push_back(msg);
        } else if (msg.priority == static_cast<int>(EventPriority::HIGH)) {
            normalPriorityQueue.push_back(msg);
        } else {
            lowPriorityQueue.push_back(msg);
        }
    }
    queueCV.notify_one();
}

// Client side implementation
void COM::runClient() {
    while (running) {
        checkQueues();
        
        // Small delay to prevent busy-waiting
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
        sendToServer(msg);
        lock.lock();
    }

    // Process normal priority only when high priority is empty
    while (!normalPriorityQueue.empty()) {
        auto msg = normalPriorityQueue.front();
        normalPriorityQueue.pop_front();
        lock.unlock();
        sendToServer(msg);
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
        normalPriorityQueue.empty() && 
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
        _pulse heartbeat;
        heartbeat.code = HEARTBEAT_CODE;
        heartbeat.value.sival_int = 0;
        heartbeat.priority = static_cast<int>(EventPriority::LOW);
        
        _client->send_event(heartbeat.code, heartbeat.value.sival_int, heartbeat.priority);
        updateHeartbeat();
    }
}

void COM::sendToServer(const _pulse& msg) {
    _client->send_event(msg.code, msg.value.sival_int, msg.priority);
    updateHeartbeat();
}

// Server side implementation
void COM::runServer() {
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
                sendToDispatcher(timeoutEvent);
            }
            // Handle other errors if needed
        }
    }
}

void COM::processMessage(const _pulse& msg) {
    // Process ES messages immediately
    if (msg.code == ESTOP_CODE) {
        sendToDispatcher(msg);
    } 
    // Process other messages
    else {
        // Add your message processing logic here
        // ...
        
        // Forward to dispatcher if needed
        sendToDispatcher(msg);
    }
}

void COM::sendToDispatcher(const _pulse& msg) {
    _dispatcherSen->send_event(msg.code, msg.value.sival_int, msg.priority);
}

void COM::updateHeartbeat() {
    lastHeartbeat = std::chrono::steady_clock::now();
}