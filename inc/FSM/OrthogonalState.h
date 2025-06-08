#ifndef ORTHOGONALSTATE_H
#define ORTHOGONALSTATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "State.h"

#include <vector>
#include <iostream>


class OrthogonalState {
    //============================================ contructors & destructors ============================================
public:
    OrthogonalState(ContextData* data);

    //copy constructor
    OrthogonalState(const OrthogonalState& other);
    virtual ~OrthogonalState();

    //================================================ public functions ================================================
public:
    virtual void entry();
    virtual void exit();

    virtual OrthogonalState* laser_front_blocked();
    virtual OrthogonalState* laser_front_unblocked();
    virtual OrthogonalState* laser_back_blocked();
    virtual OrthogonalState* laser_back_unblocked();
    virtual OrthogonalState* button_start_pressed();
    virtual OrthogonalState* button_start_released();
    virtual OrthogonalState* button_stop_pressed();
    virtual OrthogonalState* button_stop_released();
    virtual OrthogonalState* button_reset_pressed();
    virtual OrthogonalState* button_reset_released();
    virtual OrthogonalState* button_estop_pressed();
    virtual OrthogonalState* button_estop_released();
    virtual OrthogonalState* metal_detected();
    virtual OrthogonalState* metal_not_detected();
    virtual OrthogonalState* laser_sorting_gate_blocked();
    virtual OrthogonalState* laser_sorting_gate_unblocked();
    virtual OrthogonalState* laser_ramp_blocked();
    virtual OrthogonalState* laser_ramp_unblocked();
    virtual OrthogonalState* adc_top_area_blocked();
    virtual OrthogonalState* adc_top_area_unblocked();
    virtual OrthogonalState* adc_side_area_blocked();     //unused
    virtual OrthogonalState* adc_side_area_unblocked();   //unused


    virtual OrthogonalState* adc_calibration_done();
    virtual OrthogonalState* adc_new_piece();

    virtual OrthogonalState* timer(int id);



    //================================================ private variables ================================================
protected:
    ContextData* data;
    //OrthogonalState* suborthogonalstates;
    std::vector<OrthogonalState*>* list_of_suborthogonalstates;

    //================================================ private functions ================================================
private:
    OrthogonalState* handle_event_using_function(OrthogonalState* (OrthogonalState::* handler_function)());


};

#endif