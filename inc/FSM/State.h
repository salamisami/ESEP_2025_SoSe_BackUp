#ifndef STATE_H
#define STATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "I_State.h"
#include <iostream>


class State : public I_State{
    //============================================ contructors & destructors ============================================
public:
    State(ContextData* data);

    //copy constructor
    State(const State& other);
    virtual ~State() override;

    //================================================ public functions ================================================
public:
    virtual void entry() override;
    virtual void exit() override;

    virtual State* laser_front_blocked() override;
    virtual State* laser_front_unblocked() override;
    virtual State* laser_back_blocked() override;
    virtual State* laser_back_unblocked() override;
    virtual State* button_start_pressed() override;
    virtual State* button_start_released() override;
    virtual State* button_stop_pressed() override;
    virtual State* button_stop_released() override;
    virtual State* button_reset_pressed() override;
    virtual State* button_reset_released() override;
    virtual State* button_estop_pressed() override;
    virtual State* button_estop_released() override;
    virtual State* metal_detected() override;
    virtual State* metal_not_detected() override;
    virtual State* laser_sorting_gate_blocked() override;
    virtual State* laser_sorting_gate_unblocked() override;
    virtual State* laser_ramp_blocked() override;
    virtual State* laser_ramp_unblocked() override;
    virtual State* adc_top_area_blocked() override;
    virtual State* adc_top_area_unblocked() override;
    virtual State* adc_side_area_blocked() override;     //unused
    virtual State* adc_side_area_unblocked() override;   //unused


    virtual State* adc_calibration_done() override;
    virtual State* adc_new_piece() override;

    virtual State* timer(int id) override;



    //================================================ private variables ================================================
protected:
    ContextData* data;
    State* substate;

    //================================================ private functions ================================================
private:
    State* handle_event_using_function(State* (State::* handler_function)());


};

#endif