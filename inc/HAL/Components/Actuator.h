#ifndef ACTUATOR_H
#define ACTUATOR_H
#pragma once

#include "Macros.h"
#include "Event.h"
#include "Mailbox.h"

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



class Actuator {
public: //============================================ contructors & destructors ============================================
    Actuator(Mailbox<_pulse>* mailbox);
    virtual ~Actuator();


public: //================================================ public functions ================================================
    bool isGate();
    void test_outs();
    void global_shutdown();
    void reset();



private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    std::thread actuatorThread;
    std::mutex mtx;
    //pointers
    Mailbox<_pulse>* mailbox;
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;

    //primitive types
    //bool and char
    volatile bool actuatorRunning;
    bool global_estop;



private: //================================================ private functions ================================================
    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);

    void threadFunction();

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