#ifndef STATE_H
#define STATE_H
#pragma once

#include "ContextData.h"
#include "Event.h"

class State {
public: //============================================ constructors & destructors ============================================
    State(ContextData* data);
    virtual ~State() = default;


public: //================================================ public functions ================================================
    virtual void entry();
    virtual void exit();

    virtual State* clone();

    virtual State* laser_front_blocked();
    virtual State* laser_front_unblocked();
    virtual State* laser_back_blocked();
    virtual State* laser_back_unblocked();
    virtual State* button_start_pressed();
    virtual State* button_start_released();
    virtual State* button_stop_pressed();
    virtual State* button_stop_released();
    virtual State* button_reset_pressed();
    virtual State* button_reset_released();
    virtual State* button_estop_pressed();
    virtual State* button_estop_released();
    virtual State* metal_detected();
    virtual State* metal_not_detected();
    virtual State* laser_sorting_gate_blocked();
    virtual State* laser_sorting_gate_unblocked();
    virtual State* laser_ramp_blocked();
    virtual State* laser_ramp_unblocked();
    virtual State* adc_top_area_blocked();
    virtual State* adc_top_area_unblocked();
    virtual State* adc_side_area_blocked();     //unused
    virtual State* adc_side_area_unblocked();   //unused

    virtual State* com_button_estop_pressed();
    virtual State* com_button_estop_released();

    virtual State* is_pusher();
    virtual State* is_switch();


    virtual State* adc_calibration_done();
    virtual State* adc_new_piece();

    virtual State* timer(TIMER_ID id);



protected: //================================================ private variables ================================================
    //classes, STL containers, and structs
    //pointers
    ContextData* data;
    //primitive types
    //bool and char



private: //================================================ private functions ================================================
    //void privateFunction();

};

#endif