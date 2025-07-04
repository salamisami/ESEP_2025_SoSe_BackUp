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
    State(ContextData* data) : data(data) {};
    //Disable copy constructor, because we're going to use clone() instead
    State(const State& other) = delete;
    virtual ~State() = default;


public: //================================================ public functions ================================================
    /**
     * @brief Enters the state. This function must be overidden by the child state.
     */
    virtual void entry() {
        DEBUG("Warning, function of abstract class entry() is called.");
    }
    /**
     * @brief Exits the state. This function must be overidden by the child state.
     */
    virtual void exit() {
        DEBUG("Warning, function of abstract class exit() is called.");
    }
    /**
     * @brief Clones the current state.
     * @return Cloned state, which is already allocated to heap
     */
    virtual State* clone() {
        DEBUG("Warning, function of abstract class State::clone() is called.");
        return nullptr;
    }
    /**
     * @brief Returns the name of the current state.
     * @return The name of current state as string
     */
    virtual std::string get_current_state() {
        const char* state_name = typeid(*this).name();
        return demangle(state_name);
    }

    //================================================ internal events ================================================
    virtual State* timer(TIMER_ID id) {
        return nullptr;
    }

    static State* EXIT_STATE;

    virtual State* new_piece(){
        return handle_event_using_function(&State::new_piece);
    }

    virtual State* unknown_piece() {
        return handle_event_using_function(&State::unknown_piece);
    }

    virtual State* flat_piece() {
        return handle_event_using_function(&State::flat_piece);
    }

    virtual State* tall_piece() {
        return handle_event_using_function(&State::tall_piece);
    }

    virtual State* tall_w_metal_piece() {
        return handle_event_using_function(&State::tall_w_metal_piece);
    }

    virtual State* sort_out() {
        return handle_event_using_function(&State::sort_out);
    }

    virtual State* sort_out_fbm2() {
        return handle_event_using_function(&State::sort_out_fbm2);
    }

    virtual State* let_through() {
        return handle_event_using_function(&State::let_through);
    }

    virtual State* reset_to_flat() {
        return handle_event_using_function(&State::reset_to_flat);
    }

    virtual State* reset_to_tall() {
        return handle_event_using_function(&State::reset_to_tall);
    }

    virtual State* reset_to_tall_w_metal() {
        return handle_event_using_function(&State::reset_to_tall_w_metal);
    }
    //====================================================MotorPiece======================================================
    virtual State* delete_w_motor() {
        return handle_event_using_function(&State::delete_w_motor);
    }
    virtual State* motor_slow() {
        return handle_event_using_function(&State::motor_slow);
    }
    virtual State* motor_fast() {
        return handle_event_using_function(&State::motor_fast);
    }
    virtual State* motor_stop_fsm() {
        return handle_event_using_function(&State::motor_stop_fsm);
    }


    //================================================ external events ================================================


    virtual State* laser_front_blocked() {
        return handle_event_using_function(&State::laser_front_blocked);
    }

    virtual State* laser_front_unblocked() {
        return handle_event_using_function(&State::laser_front_unblocked);
    }

    virtual State* laser_back_blocked() {
        return handle_event_using_function(&State::laser_back_blocked);
    }
    virtual State* laser_back_unblocked() {
        return handle_event_using_function(&State::laser_back_unblocked);
    }

    virtual State* button_start_pressed() {
        return handle_event_using_function(&State::button_start_pressed);
    }

    virtual State* delete_w_motor(){
      return handle_event_using_function(&State::delete_w_motor);
    } 
    virtual State* motor_slow(){
      return handle_event_using_function(&State::motor_slow);
    } 
    virtual State* motor_fast(){
      return handle_event_using_function(&State::motor_fast);
    }    
    virtual State* motor_stop_fsm(){
      return handle_event_using_function(&State::motor_stop_fsm);
    }

    virtual State* button_start_released() {
        return handle_event_using_function(&State::button_start_released);
    }

    virtual State* button_stop_pressed() {
        return handle_event_using_function(&State::button_stop_pressed);
    }

    virtual State* button_stop_released() {
        return handle_event_using_function(&State::button_stop_released);
    }

    virtual State* button_reset_pressed() {
        return handle_event_using_function(&State::button_reset_pressed);
    }

    virtual State* button_reset_released() {
        return handle_event_using_function(&State::button_reset_released);
    }

    virtual State* button_estop_pressed() {
        return handle_event_using_function(&State::button_estop_pressed);
    }

    virtual State* button_estop_released() {
        return handle_event_using_function(&State::button_estop_released);
    }

    virtual State* metal_detected() {
        return handle_event_using_function(&State::metal_detected);
    }

    virtual State* metal_not_detected() {
        return handle_event_using_function(&State::metal_not_detected);
    }

    virtual State* laser_sorting_gate_blocked() {
        return handle_event_using_function(&State::laser_sorting_gate_blocked);
    }

    virtual State* laser_sorting_gate_unblocked() {
        return handle_event_using_function(&State::laser_sorting_gate_unblocked);
    }

    virtual State* laser_ramp_blocked() {
        return handle_event_using_function(&State::laser_ramp_blocked);
    }

    virtual State* laser_ramp_unblocked() {
        return handle_event_using_function(&State::laser_ramp_unblocked);
    }

    virtual State* adc_new_piece(){
        return handle_event_using_function(&State::adc_new_piece);
    }

    virtual State* adc_timeout(){
        return handle_event_using_function(&State::adc_timeout);
    }

    virtual State* adc_top_area_blocked() {
        return handle_event_using_function(&State::adc_top_area_blocked);
    }

    virtual State* adc_top_area_unblocked() {
        return handle_event_using_function(&State::adc_top_area_unblocked);
    }

    virtual State* adc_side_area_blocked() {
        return handle_event_using_function(&State::adc_side_area_blocked);
    }

    virtual State* adc_side_area_unblocked() {
        return handle_event_using_function(&State::adc_side_area_unblocked);
    }

    virtual State* adc_wh_detect(){
        return handle_event_using_function(&State::adc_wh_detect);
    }

    virtual State* adc_wf_detect(){
        return handle_event_using_function(&State::adc_wf_detect);
    }

    virtual State* adc_wb_detect(){
        return handle_event_using_function(&State::adc_wb_detect);
    }

    virtual State* adc_w_not_detect(){
        return handle_event_using_function(&State::adc_w_not_detect);
    }

    virtual State* adc_invalid_measure(){
        return handle_event_using_function(&State::adc_invalid_measure);
    }

    virtual State* com_button_estop_pressed() {
        return handle_event_using_function(&State::com_button_estop_pressed);
    }

    virtual State* com_button_estop_released() {
        return handle_event_using_function(&State::com_button_estop_released);
    }

    virtual State* com_button_reset_pressed() {
        return handle_event_using_function(&State::com_button_reset_pressed);
    }

    virtual State* new_piece_to_sort() {
        return handle_event_using_function(&State::new_piece_to_sort);
    }

    virtual State* new_piece_not_to_sort() {
        return handle_event_using_function(&State::new_piece_not_to_sort);
    }

    virtual State* heartbeat() {
        return handle_event_using_function(&State::heartbeat);
    }

    virtual State* timeout_com() {
        return handle_event_using_function(&State::timeout_com);
    }

    virtual State* reconnect() {
        return handle_event_using_function(&State::reconnect);
    }

    virtual State* ramp_full() {
        return handle_event_using_function(&State::ramp_full);
    }

    virtual State* ramp_not_full() {
        return handle_event_using_function(&State::ramp_not_full);
    }

    virtual State* fbm_2_ready() {
        return handle_event_using_function(&State::fbm_2_ready);
    }

    virtual State* fbm_2_busy() {
        return handle_event_using_function(&State::fbm_2_busy);
    }

    virtual State* request_transfer() {
        return handle_event_using_function(&State::request_transfer);
    }

    virtual State* transfer_done() {
        return handle_event_using_function(&State::transfer_done);
    }

    virtual State* transfer_failed() {
        return handle_event_using_function(&State::transfer_failed);
    }

    virtual State* transfer_start_tall() {
        return handle_event_using_function(&State::transfer_start_tall);
    }

    virtual State* transfer_start_tall_w_metal() {
        return handle_event_using_function(&State::transfer_start_tall_w_metal);
    }

    virtual State* transfer_start_flat() {
        return handle_event_using_function(&State::transfer_start_flat);
    }

    virtual State* transfer_start_other() {
        return handle_event_using_function(&State::transfer_start_other);
    }

    virtual State* adc_calibration_done() {
        return handle_event_using_function(&State::adc_calibration_done);
    }

    virtual State* is_pusher() {
        return handle_event_using_function(&State::is_pusher);
    }

    virtual State* is_switch() {
        return handle_event_using_function(&State::is_switch);
    }

    //================================================ error events ================================================
    
    virtual State* error_w_lost() {
        return handle_event_using_function(&State::error_w_lost);
    }



protected: //================================================ protected ================================================
    //classes, STL containers, and structs
    //pointers
    ContextData* data;
    //primitive types
    //bool and char

    virtual State* handle_event_using_function(State* (State::* handler_function)()) {
        return nullptr;
    }



private: //================================================ private functions ================================================
    std::string demangle(const char* mangled) {
        int status;
        char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
        std::string result = (status == 0) ? demangled : mangled;
        free(demangled);
        return result;
    }

};

#endif
