#ifndef HAL_H
#define HAL_H

#include "IHAL.h"
#include <stdint.h>
//#include <stdio.h>
#include <stdexcept>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/dispatch.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

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


class HAL :public IHAL {
public: //============================================ contructors & destructors ============================================
    HAL(std::string attach_point);
    virtual ~HAL();

public: //================================================ public functions ================================================
    bool isGate() override;

    void motor_right() override;
    void motor_left() override;
    void motor_slow_on() override;
    void motor_slow_off() override;
    void motor_stop() override;

    void traffic_red_on() override;
    void traffic_red_off() override;
    void traffic_yellow_on() override;
    void traffic_yellow_off() override;
    void traffic_green_on() override;
    void traffic_green_off() override;

    void sorting_on() override;
    void sorting_off() override;

    void led_start_on() override;
    void led_start_off() override;

    void led_reset_on() override;
    void led_reset_off() override;
    void led_q1_on() override;
    void led_q1_off() override;
    void led_q2_on() override;
    void led_q2_off() override;

    void test_outs();
    void test_ins();


private: //================================================ private variables ================================================
    uintptr_t gpio_bank_0;
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;
    //uintptr_t gpio_bank_3;

    int externalConID;
    uint32_t inputPins;
    int interruptID;
    int internalConID, channelID;
    std::thread* receivingThread;
    std::vector<uint8_t> pinsList;
    std::string attach_point;
    name_attach_t* attach;
    int last_causing_pin;
    bool last_pin_status;
    bool receivingRunning;

private: //================================================ private functions ================================================
    //outs
    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);
    void wait(float seconds);
    void setup_GNS_receiver();
    void clean_GNS_receiver();



    //ins
    void setup_GNS_sender();
    void clean_GNS_sender();
    void setup_internal_pulse_message();
    void clean_internal_pulse_message();
    void receivingRoutine(int channelID);
    void handleInterrupt(void);
    void startReceiving();
    int registerToBit(uint32_t inputRegister);
    void sendEvent(int causing_pin, int pin_status);

};

#endif
