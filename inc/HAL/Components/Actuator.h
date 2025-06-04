#ifndef ACTUATOR_H
#define ACTUATOR_H
#pragma once

#include "Macros.h"
#include "Event.h"
#include "Mailbox.h"
#include "ADC_Class.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>
#include <mutex>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <hw/inout.h>
#include <sched.h>

#define GNS_NAME "Actuator"

// Thread control structure
typedef struct {
    std::thread worker;
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic<bool> stopFlag{ false };
    std::atomic<bool> running{ false };
    std::atomic<double> frequency{ 0 };
}TrafficLight;



class Actuator {
public: //============================================ contructors & destructors ============================================
    Actuator(Mailbox<_pulse>* mailbox, ADC_Class* adc = nullptr);
    virtual ~Actuator();


public: //================================================ public functions ================================================
    bool isGate();
    bool isEstop();

    void test_outs();

    void local_estop_activate();
    void local_estop_deactivate();



private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    std::thread actuatorThread;
    std::thread trafficThread;
    std::mutex mtx;
    std::mutex green_mtx;
    std::mutex yellow_mtx;
    std::mutex red_mtx;

    TrafficLight green_;
    TrafficLight yellow_;
    TrafficLight red_;

    //pointers
    Mailbox<_pulse>* mailbox;
    ADC_Class* adc;
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;

    //primitive types
    //bool and char
    volatile bool actuatorRunning;
    bool is_local_estop;
    bool is_neighbor_estop;
    bool prohibit_operate;






private: //================================================ private functions ================================================
    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);

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

    // Worker functions
    void greenWorker();
    void yellowWorker();
    void redWorker();

    void threadFunction();
    void global_shutdown();
    void check_estop();
    void stop_moving_parts();

    void handleActuatorEvent(int event_value);
    //void handleEStop(int event_value);

    void motor_right();
    void motor_left();
    void motor_slow_on();
    void motor_slow_off();
    void motor_stop();

    void traffic_red_on();
    void traffic_red_off();
    void traffic_yellow_on();
    void traffic_yellow_off();
    void traffic_green_on();
    void traffic_green_off();

    void traffic_red_slow();
    void traffic_red_fast();
    void traffic_yellow_slow();
    void traffic_yellow_fast();
    void traffic_green_slow();
    void traffic_green_fast();



    void sorting_on();
    void sorting_off();

    void led_start_on();
    void led_start_off();

    void led_reset_on();
    void led_reset_off();
    void led_q1_on();
    void led_q1_off();
    void led_q2_on();
    void led_q2_off();



};

#endif
