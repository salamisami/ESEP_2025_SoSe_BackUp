#ifndef TRAFFIC_UTILITY_H
#define TRAFFIC_UTILITY_H

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

class TrafficUtility {
public:
    // Get the singleton instance
    static TrafficUtility& getInstance();

    // Traffic light control functions
    void trafficGreen(int frequency);
    void trafficYellow(int frequency);
    void trafficRed(int frequency);

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

private:
    TrafficUtility();
    ~TrafficUtility();

    // Worker functions
    void greenWorker();
    void yellowWorker();
    void redWorker();

    // Thread control structure
    struct TrafficLight {
        std::thread worker;
        std::mutex mutex;
        std::condition_variable cv;
        std::atomic<bool> stopFlag{false};
        std::atomic<bool> running{false};
        std::atomic<int> frequency{0};
    };

    TrafficLight green_;
    TrafficLight yellow_;
    TrafficLight red_;
};

#endif // TRAFFIC_UTILITY_H