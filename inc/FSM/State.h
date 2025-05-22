#ifndef STATE_H
#define STATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include <iostream>


class State {
    //============================================ contructors & destructors ============================================
public:
    State(ContextData* data);
    virtual ~State() = default;

    //================================================ public functions ================================================
public:
    virtual void entry() = 0;
    virtual void exit() = 0;
    
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





    //================================================ private variables ================================================
protected:
    ContextData* data;

    //================================================ private functions ================================================
private:


};

#endif