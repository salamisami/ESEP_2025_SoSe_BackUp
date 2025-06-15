#ifndef COM_H
#define COM_H

#include "QNet.h"
#include "Event.h"
#include <chrono>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>

class COM {
public:
    COM(I_Receiver* server, I_Sender* client, 
        I_Receiver* dispatcherRec, I_Sender* dispatcherSen);
    ~COM();
    
    void start();
    void stop();
    void addMessage(const _pulse& msg);

private:
    // Client side
    void runClient();
    void checkQueues();
    void sendHeartbeat();
    void sendToServer(const _pulse& msg, int priority = (int) EventPriority::DEFAULT);
    
    // Server side
    void runServer();
    void processMessage(const _pulse& msg);
    void sendToDispatcher(const _pulse& msg, int priority = (int) EventPriority::DEFAULT);
    void updateHeartbeat();
    
    // Shared state
    I_Receiver* _server;
    I_Sender* _client;

    I_Receiver* _dispatcherRec;
    I_Sender* _dispatcherSen;
    std::chrono::steady_clock::time_point lastHeartbeat;
    bool running;

    
    std::deque<_pulse> highPriorityQueue;
    std::deque<_pulse> lowPriorityQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    
    std::thread clientThread;
    std::thread serverThread;
    
    // Constants
    static constexpr int HEARTBEAT_INTERVAL = 5;
    static constexpr int HEARTBEAT_TIMEOUT = 15;
    static constexpr int HEARTBEAT_CODE = 0xFF;
    static constexpr int ESTOP_CODE = 0x01;
    static constexpr int TIMEOUT_CODE = 0xFE;
};

#endif // COM_H
