#ifndef ORTHOGONALSTATE_H
#define ORTHOGONALSTATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "I_State.h"

#include <vector>
#include <iostream>


class OrthogonalState : public I_State {
    //============================================ contructors & destructors ============================================
public:
    OrthogonalState(ContextData* data, std::vector<I_State*>* initial_substates);
    OrthogonalState(const OrthogonalState&) = delete;
    virtual ~OrthogonalState() override;

    //================================================ public functions ================================================
public:
    virtual void entry() override;
    virtual void exit() override;

    virtual OrthogonalState* clone() override;

    virtual I_State* laser_front_blocked() override;
    virtual I_State* laser_front_unblocked() override;
    virtual I_State* laser_back_blocked() override;
    virtual I_State* laser_back_unblocked() override;
    virtual I_State* button_start_pressed() override;
    virtual I_State* button_start_released() override;
    virtual I_State* button_stop_pressed() override;
    virtual I_State* button_stop_released() override;
    virtual I_State* button_reset_pressed() override;
    virtual I_State* button_reset_released() override;
    virtual I_State* button_estop_pressed() override;
    virtual I_State* button_estop_released() override;
    virtual I_State* metal_detected() override;
    virtual I_State* metal_not_detected() override;
    virtual I_State* laser_sorting_gate_blocked() override;
    virtual I_State* laser_sorting_gate_unblocked() override;
    virtual I_State* laser_ramp_blocked() override;
    virtual I_State* laser_ramp_unblocked() override;
    virtual I_State* adc_top_area_blocked() override;
    virtual I_State* adc_top_area_unblocked() override;
    virtual I_State* adc_side_area_blocked() override;     //unused
    virtual I_State* adc_side_area_unblocked() override;   //unused


    virtual I_State* adc_calibration_done() override;
    virtual I_State* adc_new_piece() override;

    virtual I_State* timer(int id) override;



    //================================================ private variables ================================================
protected:
    ContextData* data;
    std::vector<I_State*>* substates;

    //================================================ private functions ================================================
private:
    I_State* handle_event_using_function(I_State* (I_State::* handler_function)());


};

#endif