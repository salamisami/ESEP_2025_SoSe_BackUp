#ifndef HAL_H
#define HAL_H

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

#include <sys/mman.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <hw/inout.h>


//
//#include "simqnxgpioapi.h"
//#include "simqnxirqapi.h"

#include "Event.h"

#pragma once



//#define SHOW_EVENTS

/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2
#define INTERRUPT_PULSE _PULSE_CODE_MINAVAIL + 3




class HAL {
public: //============================================ contructors & destructors ============================================
    HAL(std::string attach_point);
    HAL();
    virtual ~HAL();

public: //================================================ public functions ================================================
    bool isGate();

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

    void test_outs();
    void test_ins();


private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    std::vector<uint8_t> pinsList;
    std::thread* interruptThread;
    std::thread* actuatorThread;
    std::string attach_point;

    //pointers
    uintptr_t gpio_bank_0;
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;
    //uintptr_t gpio_bank_3;
    name_attach_t* attach;

    //primitive types
    uint32_t inputPins;
    int externalConID;
    int externalChannelID;
    int interruptID;
    int internalConnectionID;
    int internalChannelID;
    int last_causing_pin;


    //bool and char
    bool test_mode;
    int last_pin_status;
    bool interruptRunning;
    volatile bool actuatorRunning;






private: //================================================ private functions ================================================
    //outs
    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);
    void wait(float seconds);
    void setup_GNS_receiver();
    void clean_GNS_receiver();



    //ins
    void setup_interrupts();
    int setup_GNS_sender();
    void clean_GNS_sender();
    void setup_internal_pulse_message();
    void clean_internal_pulse_message();
    void interruptFunction(int channelID);
    void actuatorFunction(int chid);
    void isr(void);
    int registerToBit(uint32_t inputRegister);
    void sendEvent(int causing_pin, int pin_status);

};

#endif