#ifndef IHAL_H
#define IHAL_H

#pragma once

//those are the events
#define LASER_FRONT_BLOCKED
#define LASER_FRONT_UNBLOCKED
#define LASER_BACK_BLOCKED
#define LASER_BACK_UNBLOCKED

#define BUTTON_START_PRESSED
#define BUTTON_START_UNPRESSED
#define BUTTON_STOP_PRESSED
#define BUTTON_STOP_UNPRESSED
#define BUTTON_RESET_PRESSED
#define BUTTON_RESET_UNPRESSED
#define BUTTON_ESTOP_PRESSED
#define BUTTON_ESTOP_UNPRESSED

#define METAL_DETECTED
#define METAL_NOT_DETECTED

#define LASER_SORTING_GATE_BLOCKED
#define LASER_SORTING_GATE_UNBLOCKED
#define LASER_RAMP_BLOCKED
#define LASER_RAMP_UNBLOCKED

class IHAL {
public:
    virtual ~IHAL() = default;

    //OUTs
    virtual bool isGate() = 0;

    virtual void motor_right() = 0;
    virtual void motor_left() = 0;
    virtual void motor_slow_on() = 0;
    virtual void motor_slow_off() = 0;
    virtual void motor_stop() = 0;

    

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
