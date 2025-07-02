#ifndef STATE_H
#define STATE_H
#pragma once

#include "ContextData.h"
#include "Event.h"

#include <typeinfo>
#include <cxxabi.h>

class State {
public: //============================================ constructors & destructors ============================================
    /**
     * @brief State is a very basic state, containing only entry and exit. It does not contain any substates or orthogonal states.
     * @param data a global context data, which should be visible across the states
     */
    State(ContextData* data);
    //Disable copy constructor, because we're going to use clone() instead
    State(const State& other) = delete;
    virtual ~State() = default;


public: //================================================ public functions ================================================
    /**
     * @brief Enters the state. This function must be overidden by the child state.
     */
    virtual void entry();
    /**
     * @brief Exits the state. This function must be overidden by the child state.
     */
    virtual void exit();
    /**
     * @brief Clones the current state.
     * @return Cloned state, which is already allocated to heap
     */
    virtual State* clone();
    /**
     * @brief Returns the name of the current state.
     * @return The name of current state as string
     */
    virtual std::string get_current_state();

    //================================================ internal events ================================================
    virtual State* timer(TIMER_ID id);
    
    virtual State* sort_out();
    virtual State* sort_out_fbm2();
    virtual State* let_through();
    virtual State* check_piece();
    virtual State* reset_to_flat();
    virtual State* reset_to_tall();
    virtual State* reset_to_tall_w_metal();



    //================================================ external events ================================================

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

     //neue States
    virtual State* ramp_full();
    virtual State* ramp_not_full();
    virtual State* sorting_out();
    //virtual State* error_both_r_full();
    virtual State* error_pieces_too_close_fixed();
    virtual State* unblock_starting_area();

    //neue COM States
    virtual State* com_ramp_full();
    virtual State* com_ramp_not_full();


    //States für ErrorHandler
    virtual State* error_c_lost_com();
    virtual State* error_c_lost_nr();
    virtual State* error_c_lost_mqtt();
    virtual State* com_connected();
    virtual State* mqtt_connected();
    virtual State* adc_invalid_measure();
    virtual State* cant_find_calb_conf();
    virtual State* cant_find_rep_conf();
    virtual State* error_w_lost();
    virtual State* error_w_appear();




protected: //================================================ private variables ================================================
    //classes, STL containers, and structs
    //pointers
    ContextData* data;
    //primitive types
    //bool and char



private: //================================================ private functions ================================================
    std::string demangle(const char* mangled);

};

#endif