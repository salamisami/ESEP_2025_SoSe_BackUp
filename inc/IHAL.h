#ifndef IHAL_H
#define IHAL_H

#pragma once

//implementing with interrupt is preffered
//therefore HAL will contain only outs at the moment
#define USE_INTERRUPT

class IHAL {
public:
    virtual ~IHAL() = default;

    #ifndef USE_INTERRUPT
    //INs
    bool laser_front_is_blocked();
    bool laser_back_is_blocked();

	bool metal_sensor_detects();
    double laser_measure_value();

    bool laser_sorting_gate_is_blocked();
    bool laser_ramp_is_blocked();

    bool button_start_is_pressed();
    bool button_stop_is_pressed();
    bool button_reset_is_pressed();
    bool button_estop_is_pressed();
    #endif

    //OUTs
    virtual void motor_right_on();
    virtual void motor_right_off();
    virtual void motor_left_on();
    virtual void motor_left_off();
    virtual void motor_slow_on();
    virtual void motor_slow_off();

    virtual void motor_stop_on();
    virtual void motor_stop_off();

    virtual void traffic_red_on();
    virtual void traffic_red_off();
    virtual void traffic_yellow_on();
    virtual void traffic_yellow_off();
    virtual void traffic_green_on();
    virtual void traffic_green_off();

    virtual void sorting_open();
    virtual void sorting_close();

    virtual void led_start_on();
    virtual void led_start_off();

    virtual void led_reset_on();
    virtual void led_reset_off();
    virtual void led_q1_on();
    virtual void led_q1_off();
    virtual void led_q2_on();
    virtual void led_q2_off();

private:

};

#endif
