#include <iostream>
#include "TrafficUtility.h"
#include "Thread_COM.h"

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    auto& traffic = TrafficUtility::getInstance();
    
    traffic.trafficGreen(0.5);  // Green light at 1Hz
    traffic.trafficYellow(2); // Yellow light at 2Hz
    traffic.trafficRed(5);  // Red light at 0.5Hz
    
    // Let them run for 10 seconds
    std::this_thread::sleep_for(std::chrono::seconds(100));
    
    traffic.stopAll();
    return 0;
}
