#ifndef COM_H
#define COM_H

// --- Standard-C++ und QNX/Netzwerk-Header ---
#include <chrono>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>
#include <iostream>

// QNX/Socket/Netzwerk
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/neutrino.h>

// Dein Projekt
#include "QNet.h"
#include "Event.h"
#include "Thread_COM.h"

#define COUT(msg) std::cout << msg << std::endl

#define HEARTBEAT_MULTIPLIER 1
#define HEARTBEAT_INTERVAL 100 * HEARTBEAT_MULTIPLIER
#define TIMEOUT_COM_INTERVAL HEARTBEAT_MULTIPLIER * 1000000ULL
#define UDP_WATCHDOG_TIMEOUT 1

// ===== UDP-Watchdog Settings =====
#define UDP_WATCHDOG_PORT       12345
#define UDP_WATCHDOG_PERIOD_MS  500
#define UDP_WATCHDOG_TIMEOUT_MS 2000
#define PEER_UDP_IP "192.168.101.108" // ANPASSEN!
#define LOCAL_UDP_IP "0.0.0.0"
// ================================

class COM
{
public:
    COM(I_Receiver *server, const char *clientSendName,
        I_Receiver *dispatcherRec, I_Sender *dispatcherSen);
    ~COM();

    void start();
    void stop();

private:
    // Client
    void runClient();
    void checkQueues();
    void sendHeartbeat();
    int sendToServer(const _pulse &msg, int priority = (int)EventPriority::DEFAULT);

    void runDispatcher();

    // Handler functions for different topics
    void handleInterruptTopic(int originalValue, _pulse& dispatcherMsg);
    void handleInternalTopic(int originalValue, _pulse& dispatcherMsg);
    void handleComTopic(int originalValue, _pulse& dispatcherMsg);
    void handleRemConTopic(int originalValue, _pulse& dispatcherMsg);

    // Server
    void runServer();
    void processMessage(const _pulse &msg);
    void sendToDispatcher(const _pulse &msg, int priority = (int)EventPriority::SECOND_PRIO);
    void updateHeartbeat();
    void handle_QNX_pulse(_pulse *msg, int rcvid);
    void handle_QNX_IO_msg(_pulse *msg, int rcvid);

    // --- UDP-Watchdog ---
    std::thread udpWatchdogThread;
    bool udpWatchdogRunning;
    bool udpWatchdogLost;
    void runUdpWatchdog();
    void notifyUdpLost();
    void notifyUdpRestored();

    // Shared state
    I_Receiver *_server;
    const char *_clientSendName;
    std::unique_ptr<Thread_COM::Sender> _client;
    std::mutex _clientMutex;

    I_Receiver *_dispatcherRec;
    I_Sender *_dispatcherSen;
    std::chrono::steady_clock::time_point lastHeartbeat;
    bool disconnected = true;
    bool running;
    bool rampfull = false;
    bool mqttConnected = false;

    std::deque<_pulse> highPriorityQueue;
    std::deque<_pulse> lowPriorityQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;

    std::thread clientThread;
    std::thread serverThread;
    std::thread dispatcherThread;

    // Constants 
    template <typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args &&...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};

#endif // COM_H
