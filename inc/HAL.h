#ifndef HAL_H
#define HAL_H

#include "IHAL.h"
#include <stdint.h>

#pragma once


class HAL :public IHAL {
public:
    HAL();
    virtual ~HAL();

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

private:
    uintptr_t gpio_bank_0;
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;
    uintptr_t gpio_bank_3;

    void set_data(uintptr_t gpio_bank, uint32_t bit);
    void clear_data(uintptr_t gpio_bank, uint32_t bit);

};

#endif
