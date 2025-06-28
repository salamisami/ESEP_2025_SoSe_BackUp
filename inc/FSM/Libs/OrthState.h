#ifndef ORTHSTATE_H
#define ORTHSTATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "State.h"

#include <vector>
#include <iostream>


class OrthState : public State {
    //============================================ constructors & destructors ============================================
public:
    /**
     * @brief OrthState is an orthogonal state. It contains more than one substates, which are running parallel. This OrthState also contains entry and exit functions.
     * @param data a global context data. The data will be forwarded to parent class (State)
     * @param initial_substate the initial substates inside this state
     */
    OrthState(ContextData* data, std::vector<State*> initial_substates);
    //Disable copy constructor, because we're going to use clone() instead
    OrthState(const OrthState&) = delete;
    virtual ~OrthState() override;

    //================================================ public functions ================================================
public:
    virtual void entry() override;
    virtual void exit() override;

    //TODO make virtual
    virtual State* clone() override;

    /**
     * @brief adds one substate to run parallel among with other existing substates. This function will also call the entry() of the new added substate.
     * @param input_state substate to add
     */
    void spawn_orthogonal_state(State* input_state);
    
    virtual std::string get_current_state() override;

    //================================================ internal events ================================================
    virtual State* timer(TIMER_ID id) override;

    virtual State* sort_out() override;
    virtual State* sort_out_fbm2() override;
    virtual State* let_through() override;
    virtual State* check_piece() override;
    virtual State* reset_to_flat() override;
    virtual State* reset_to_tall() override;
    virtual State* reset_to_tall_w_metal() override;

    //================================================ external events ================================================

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

    //neue States
    virtual State* ramp_full() override;
    virtual State* ramp_not_full() override;
    virtual State* sorting_out() override;
    //virtual State* error_both_r_full() override;
    virtual State* error_pieces_too_close_fixed() override;

    //neue COM States
    virtual State* com_ramp_full() override;
    virtual State* com_ramp_not_full() override;

    virtual State* com_button_estop_pressed() override;
    virtual State* com_button_estop_released() override;

    virtual State* is_pusher() override;
    virtual State* is_switch() override;



    //================================================ private variables ================================================
protected:
    std::vector<State*> substates;
    std::vector<State*> clone_substates();

    //================================================ private functions ================================================
private:
    State* handle_event_using_function(State* (State::* handler_function)());
    


};

#endif