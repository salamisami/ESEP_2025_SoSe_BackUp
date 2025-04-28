#ifndef HAL_H
#define HAL_H

#define SKIP_INTERFACE

#ifndef SKIP_INTERFACE
#include "IHAL.h"
#endif


#include <stdint.h>

#pragma once


class HAL
#ifndef SKIP_INTERFACE
:public IHAL
#endif
{
public:
    HAL();
    virtual ~HAL();

#ifndef SKIP_INTERFACE
    void motor_right_on() override;
    void motor_right_off() override;
    void motor_left_on() override;
    void motor_left_off() override;
    void motor_slow_on() override;
    void motor_slow_off() override;

    void motor_stop_on() override;
    void motor_stop_off() override;

    void traffic_red_on() override;
    void traffic_red_off() override;
    void traffic_yellow_on() override;
    void traffic_yellow_off() override;
    void traffic_green_on() override;
    void traffic_green_off() override;

    void sorting_open() override;
    void sorting_close() override;

    void led_start_on() override;
    void led_start_off() override;

    void led_reset_on() override;
    void led_reset_off() override;
    void led_q1_on() override;
    void led_q1_off() override;
    void led_q2_on() override;
    void led_q2_off() override;
#else
    void motor_right_on();
    void motor_right_off();
    void motor_left_on();
    void motor_left_off();
    void motor_slow_on();
    void motor_slow_off();

    void motor_stop_on();
    void motor_stop_off();

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
#endif

private:
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;
    uintptr_t gpio_bank_3;

    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);

};

#endif
