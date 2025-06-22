#ifndef COM_H
#define COM_H

#include "QNet.h"
#include "Event.h"
#include "Thread_COM.h"
#include <chrono>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>


#define COUT(msg) std::cout << msg << std::endl

class COM {
public:
    COM(I_Receiver* server, const char* clientSendName,
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
    
    void runDispatcher();

    // Server side
    void runServer();
    void processMessage(const _pulse& msg);
    void sendToDispatcher(const _pulse& msg, int priority = (int) EventPriority::DEFAULT);
    void updateHeartbeat();
    
    // Shared state
    I_Receiver* _server;
    const char* _clientSendName;
    std::unique_ptr<I_Sender> _client;  // Automatically nullptr by default

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
    std::thread dispatcherThread;
    
    // Constants
    static constexpr int HEARTBEAT_INTERVAL = 5;
    static constexpr int HEARTBEAT_TIMEOUT = 15;
    static constexpr int HEARTBEAT_CODE = 0xFF;
    static constexpr int TIMEOUT_CODE = 0xFE;

    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};


#endif // COM_H
