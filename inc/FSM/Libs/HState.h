#ifndef HSTATE_H
#define HSTATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "State.h"
#include <iostream>


class HState : public State {
    //============================================ constructors & destructors ============================================
public:
    /**
     * @brief HState is a hierarchial state. It contains one substate as a pointer. This HState also contains entry and exit functions.
     * @param data a global context data. The data will be forwarded to parent class (State)
     * @param initial_substate the initial of the substate inside this hierarchial state
     */
    HState(ContextData* data, State* initial_substate);

    //Disable copy constructor, because we're going to use clone() instead
    HState(const HState& other) = delete;
    virtual ~HState() override;

    //================================================ public functions ================================================
public:
    virtual void entry() override;
    virtual void exit() override;

    //TODO make virtual
    virtual State* clone() override;
    virtual std::string get_current_state() override;

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

    virtual State* com_button_estop_pressed() override;
    virtual State* com_button_estop_released() override;

    virtual State* is_pusher() override;
    virtual State* is_switch() override;




    virtual State* adc_calibration_done() override;

    virtual State* timer(TIMER_ID id) override;



    //================================================ private variables ================================================
protected:
    State* substate;

    //================================================ private functions ================================================
private:
    State* handle_event_using_function(State* (State::* handler_function)());


};

#endif