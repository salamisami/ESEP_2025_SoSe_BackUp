#ifndef TRAFFIC_UTILITY_H
#define TRAFFIC_UTILITY_H

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

#include "Thread_COM.h"
#include "QNet.h"
#include "Event.h"

class TrafficUtility {
public:

    static TrafficUtility& getInstance();
    static TrafficUtility& getInstance(I_Sender* sender);

    ~TrafficUtility();
    // Traffic light control functions
    void trafficGreen(double frequency);
    void trafficYellow(double frequency);
    void trafficRed(double frequency);

    // Stop all traffic lights
    void stopAll();
    void stopGreen();
    void stopYellow();
    void stopRed();

    // Check status
    bool isGreenRunning() const;
    bool isYellowRunning() const;
    bool isRedRunning() const;

    // Prevent copying
    TrafficUtility(const TrafficUtility&) = delete;
    TrafficUtility& operator=(const TrafficUtility&) = delete;
    TrafficUtility(TrafficUtility&&) = delete;
    TrafficUtility& operator=(TrafficUtility&&) = delete;

private:
    TrafficUtility();
    TrafficUtility(I_Sender* sender);
    I_Sender* traffic_sender;

    static std::mutex instanceMutex_;
    static std::unique_ptr<TrafficUtility> instance_;

    // Worker functions
    void greenWorker();
    void yellowWorker();
    void redWorker();

    void sendLightPulse(ActuatorEnum state);

    // Thread control structure
    struct TrafficLight {
        std::thread worker;
        std::mutex mutex;
        std::condition_variable cv;
        std::atomic<bool> stopFlag{false};
        std::atomic<bool> running{false};
        std::atomic<double> frequency{0};
    };

    TrafficLight green_;
    TrafficLight yellow_;
    TrafficLight red_;
};

#endif // TRAFFIC_UTILITY_H
