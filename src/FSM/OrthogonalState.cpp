#include "OrthogonalState.h"
#include <assert.h>

//================================================= contructors & destructors =================================================
OrthogonalState::OrthogonalState(ContextData* data, std::vector<I_State*>* initial_substates)
    : data(data)
    , substates(initial_substates) {
    //std::cout << "OrthogonalState Constructor" << std::endl;

}



OrthogonalState::~OrthogonalState() {
    //std::cout << "OrthogonalState Destructor" << std::endl;
    if(substates != nullptr) {
        for(I_State* current_substate : *substates) {
            delete current_substate;
        }
        delete substates;
    }
}

//===================================================== private functions =====================================================

I_State* OrthogonalState::handle_event_using_function(I_State* (I_State::* handler_function)()) {
    for(I_State* current_substate : *substates) {
        I_State* newSubstate = (current_substate->*handler_function)();
        if(newSubstate != nullptr) {
            // there is substate change, change only the substate
            current_substate->exit();
            //TODO what's wrong with this delete 
            //delete current_substate;
            current_substate = newSubstate;
            current_substate->entry();
        }
    }
    return nullptr;
}


//===================================================== public functions =====================================================

void OrthogonalState::entry() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    for(I_State* current_substate : *substates) {
        current_substate->entry();
    }
}

void OrthogonalState::exit() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    for(I_State* current_substate : *substates) {
        current_substate->exit();
    }
}


OrthogonalState* OrthogonalState::clone() {
    //TODO make a clone function here to act as a copy constructor
    return nullptr;
}

I_State* OrthogonalState::timer(int id) {
    for(I_State* current_substate : *substates) {
        I_State* newSubstate = current_substate->timer(id);
        if(newSubstate != nullptr) {
            // there is substate change, change only the substate
            current_substate->exit();
            //TODO what's wrong with the delete substates?
            //delete substates;
            current_substate = newSubstate;
            current_substate->entry();
        }
    }
    return nullptr;
}


I_State* OrthogonalState::laser_front_blocked() {
    return handle_event_using_function(&I_State::laser_front_blocked);
}

I_State* OrthogonalState::laser_front_unblocked() {
    return handle_event_using_function(&I_State::laser_front_unblocked);
}

I_State* OrthogonalState::laser_back_blocked() {
    return handle_event_using_function(&I_State::laser_back_blocked);
}

I_State* OrthogonalState::laser_back_unblocked() {
    return handle_event_using_function(&I_State::laser_back_unblocked);
}

I_State* OrthogonalState::button_start_pressed() {
    return handle_event_using_function(&I_State::button_start_pressed);
}

I_State* OrthogonalState::button_start_released() {
    return handle_event_using_function(&I_State::button_start_released);
}

I_State* OrthogonalState::button_stop_pressed() {
    return handle_event_using_function(&I_State::button_stop_pressed);
}

I_State* OrthogonalState::button_stop_released() {
    return handle_event_using_function(&I_State::button_stop_released);
}

I_State* OrthogonalState::button_reset_pressed() {
    return handle_event_using_function(&I_State::button_reset_pressed);
}

I_State* OrthogonalState::button_reset_released() {
    return handle_event_using_function(&I_State::button_reset_released);
}

I_State* OrthogonalState::button_estop_pressed() {
    return handle_event_using_function(&I_State::button_estop_pressed);
}

I_State* OrthogonalState::button_estop_released() {
    return handle_event_using_function(&I_State::button_estop_released);
}

I_State* OrthogonalState::metal_detected() {
    return handle_event_using_function(&I_State::metal_detected);
}

I_State* OrthogonalState::metal_not_detected() {
    return handle_event_using_function(&I_State::metal_not_detected);
}

I_State* OrthogonalState::laser_sorting_gate_blocked() {
    return handle_event_using_function(&I_State::laser_sorting_gate_blocked);
}

I_State* OrthogonalState::laser_sorting_gate_unblocked() {
    return handle_event_using_function(&I_State::laser_sorting_gate_unblocked);
}

I_State* OrthogonalState::laser_ramp_blocked() {
    return handle_event_using_function(&I_State::laser_ramp_blocked);
}

I_State* OrthogonalState::laser_ramp_unblocked() {
    return handle_event_using_function(&I_State::laser_ramp_unblocked);
}

I_State* OrthogonalState::adc_top_area_blocked() {
    return handle_event_using_function(&I_State::adc_top_area_blocked);
}

I_State* OrthogonalState::adc_top_area_unblocked() {
    return handle_event_using_function(&I_State::adc_top_area_unblocked);
}

I_State* OrthogonalState::adc_side_area_blocked() {
    return handle_event_using_function(&I_State::adc_side_area_blocked);
}

I_State* OrthogonalState::adc_side_area_unblocked() {
    return handle_event_using_function(&I_State::adc_side_area_unblocked);
}

I_State* OrthogonalState::adc_calibration_done() {
    return handle_event_using_function(&I_State::adc_calibration_done);
}

I_State* OrthogonalState::adc_new_piece() {
    return handle_event_using_function(&I_State::adc_new_piece);
}