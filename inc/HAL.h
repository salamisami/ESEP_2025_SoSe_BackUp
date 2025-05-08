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

//
//#include "simqnxgpioapi.h"
//#include "simqnxirqapi.h"
#include <sys/mman.h>
#include <hw/inout.h>

#pragma once

//GPIO_0 - Sensors pin mapping
#define LASER_FRONT_BIT     2
#define ADC_SIDE_AREA_BIT   3
#define ADC_AREA_BIT        4
#define LASER_SORTING_BIT   5
#define LASER_METAL_BIT     7
#define SORTING_STATUS_BIT  14
#define LASER_RAMP_BIT      15
#define LASER_BACK_BIT      20
#define BUTTON_START_BIT    22
#define BUTTON_STOP_BIT     23
#define BUTTON_RESET_BIT    26
#define BUTTON_ESTOP_BIT    27

//GPIO_1 - Internal actuator pin mapping
#define MOTOR_RIGHT_BIT     12
#define MOTOR_LEFT_BIT      13
#define MOTOR_SLOW_BIT      14
#define MOTOR_STOP_BIT      15 //useless?
#define TRAFFIC_RED_BIT     16
#define TRAFFIC_YELLOW_BIT  17
#define TRAFFIC_GREEN_BIT   18
#define SORTING_BIT         19

//GPIO_2 - External actuator pin mapping
#define LED_START_BIT       2
#define LED_RESET_BIT       3
#define LED_Q1_BIT          4
#define LED_Q2_BIT          5

//#define SHOW_EVENTS


class HAL :public IHAL {
public:
    HAL(int connectionID);
    virtual ~HAL();

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
    void test_ins(int externalChannelID);
    

private:
    uintptr_t gpio_bank_0;
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;
    //uintptr_t gpio_bank_3;

    int externalConID;
    int last_causing_pin;
    int last_pin_status;
    uint32_t inputPins;
    int interruptID;
    int channelID, internalConID;
    std::thread* receivingThread;
    std::vector<uint8_t> pinsList;
    bool receivingRunning;

private:
    //outs
    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);
    void wait(float seconds);

   

    //ins
    void receivingRoutine(int channelID);
    void handleInterrupt(void);
    void startReceiving();
    int registerToBit(uint32_t inputRegister);

};

#endif
