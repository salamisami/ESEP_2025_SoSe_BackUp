#include "TrafficUtility.h"
#include <chrono>
#include <iostream>

TrafficUtility& TrafficUtility::getInstance() {
    static TrafficUtility instance;
    return instance;
}

TrafficUtility::TrafficUtility() = default;

TrafficUtility::~TrafficUtility() {
    stopAll();
}

void TrafficUtility::trafficGreen(int frequency) {
    std::lock_guard<std::mutex> lock(green_.mutex);
    if (green_.running) stopGreen();
    
    green_.frequency = frequency;
    green_.stopFlag = false;
    green_.running = true;
    green_.worker = std::thread(&TrafficUtility::greenWorker, this);
}

void TrafficUtility::trafficYellow(int frequency) {
    std::lock_guard<std::mutex> lock(yellow_.mutex);
    if (yellow_.running) stopYellow();
    
    yellow_.frequency = frequency;
    yellow_.stopFlag = false;
    yellow_.running = true;
    yellow_.worker = std::thread(&TrafficUtility::yellowWorker, this);
}

void TrafficUtility::trafficRed(int frequency) {
    std::lock_guard<std::mutex> lock(red_.mutex);
    if (red_.running) stopRed();
    
    red_.frequency = frequency;
    red_.stopFlag = false;
    red_.running = true;
    red_.worker = std::thread(&TrafficUtility::redWorker, this);
}

void TrafficUtility::stopGreen() {
    {
        std::lock_guard<std::mutex> lock(green_.mutex);
        if (!green_.running) return;
        green_.stopFlag = true;
        green_.cv.notify_all();
    }
    if (green_.worker.joinable()) green_.worker.join();
    green_.running = false;
}

void TrafficUtility::stopYellow() {
    {
        std::lock_guard<std::mutex> lock(yellow_.mutex);
        if (!yellow_.running) return;
        yellow_.stopFlag = true;
        yellow_.cv.notify_all();
    }
    if (yellow_.worker.joinable()) yellow_.worker.join();
    yellow_.running = false;
}

void TrafficUtility::stopRed() {
    {
        std::lock_guard<std::mutex> lock(red_.mutex);
        if (!red_.running) return;
        red_.stopFlag = true;
        red_.cv.notify_all();
    }
    if (red_.worker.joinable()) red_.worker.join();
    red_.running = false;
}

void TrafficUtility::stopAll() {
    stopGreen();
    stopYellow();
    stopRed();
}

bool TrafficUtility::isGreenRunning() const { return green_.running; }
bool TrafficUtility::isYellowRunning() const { return yellow_.running; }
bool TrafficUtility::isRedRunning() const { return red_.running; }

void TrafficUtility::greenWorker() {
    while (!green_.stopFlag) {
        auto start = std::chrono::steady_clock::now();
        
        {
            std::unique_lock<std::mutex> lock(green_.mutex);
            std::cout << "GREEN light pulse at " << green_.frequency << "Hz\n";
            
            auto period = std::chrono::milliseconds(1000 / green_.frequency);
            green_.cv.wait_for(lock, period - (std::chrono::steady_clock::now() - start),
                             [this] { return green_.stopFlag; });
        }
    }
}

void TrafficUtility::yellowWorker() {
    while (!yellow_.stopFlag) {
        auto start = std::chrono::steady_clock::now();
        
        {
            std::unique_lock<std::mutex> lock(yellow_.mutex);
            std::cout << "YELLOW light pulse at " << yellow_.frequency << "Hz\n";
            
            auto period = std::chrono::milliseconds(1000 / yellow_.frequency);
            yellow_.cv.wait_for(lock, period - (std::chrono::steady_clock::now() - start),
                              [this] { return yellow_.stopFlag; });
        }
    }
}

void TrafficUtility::redWorker() {
    while (!red_.stopFlag) {
        auto start = std::chrono::steady_clock::now();
        
        {
            std::unique_lock<std::mutex> lock(red_.mutex);
            std::cout << "RED light pulse at " << red_.frequency << "Hz\n";
            
            auto period = std::chrono::milliseconds(1000 / red_.frequency);
            red_.cv.wait_for(lock, period - (std::chrono::steady_clock::now() - start),
                           [this] { return red_.stopFlag; });
        }
    }
}