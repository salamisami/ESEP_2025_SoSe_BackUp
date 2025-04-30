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
    virtual bool laser_front_is_blocked() = 0;
    virtual bool laser_back_is_blocked() = 0;

	virtual bool metal_sensor_detects() = 0;
    double laser_measure_value() = 0;

    virtual bool laser_sorting_gate_is_blocked() = 0;
    virtual bool laser_ramp_is_blocked() = 0;

    virtual bool button_start_is_pressed() = 0;
    virtual bool button_stop_is_pressed() = 0;
    virtual bool button_reset_is_pressed() = 0;
    virtual bool button_estop_is_pressed() = 0;
    #endif

    //OUTs
    virtual void motor_right_on() = 0;
    virtual void motor_right_off() = 0;
    virtual void motor_left_on() = 0;
    virtual void motor_left_off() = 0;
    virtual void motor_slow_on() = 0;
    virtual void motor_slow_off() = 0;

    virtual void motor_stop_on() = 0;
    virtual void motor_stop_off() = 0;

    virtual void traffic_red_on() = 0;
    virtual void traffic_red_off() = 0;
    virtual void traffic_yellow_on() = 0;
    virtual void traffic_yellow_off() = 0;
    virtual void traffic_green_on() = 0;
    virtual void traffic_green_off() = 0;

    virtual void sorting_on() = 0;
    virtual void sorting_off() = 0;

    virtual void led_start_on() = 0;
    virtual void led_start_off() = 0;

    virtual void led_reset_on() = 0;
    virtual void led_reset_off() = 0;
    virtual void led_q1_on() = 0;
    virtual void led_q1_off() = 0;
    virtual void led_q2_on() = 0;
    virtual void led_q2_off() = 0;

private:

};

#endif
