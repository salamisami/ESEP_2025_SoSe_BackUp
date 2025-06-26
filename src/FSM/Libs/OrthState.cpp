#include "OrthState.h"
#include <assert.h>

//================================================= constructors & destructors =================================================
OrthState::OrthState(ContextData* data, std::vector<State*> initial_substates)
    : State(data)
    , substates(initial_substates) {
    //std::cout << "OrthState Constructor" << std::endl;

}



OrthState::~OrthState() {
    //std::cout << "OrthState Destructor" << std::endl;
    for(auto& current_substate : substates) {
        delete current_substate;
    }
}

//===================================================== private functions =====================================================

State* OrthState::handle_event_using_function(State* (State::* handler_function)()) {
    for(auto& current_substate : substates) {
        State* newSubstate = (current_substate->*handler_function)();
        if(newSubstate != nullptr) {
            // there is substate change, change only the substate
            current_substate->exit();
            delete current_substate;
            current_substate = newSubstate;
            current_substate->entry();
        }
    }
    return nullptr;
}

//explicit exit
// State* StateA::service() {
//     for(auto& current_substate : substates) {
//         State* newSubstate = current_substate->service();
//         if(newSubstate != nullptr) {
//             return newSubstate;
//         }
//     }
//     return nullptr;
// }


//===================================================== public functions =====================================================

void OrthState::entry() {
    //PRINT_STATE;
    for(auto& current_substate : substates) {
        current_substate->entry();
    }
}

void OrthState::exit() {
    //PRINT_STATE;
    for(auto& current_substate : substates) {
        current_substate->exit();
    }
}

std::vector<State*> OrthState::clone_substates() {
    std::vector<State*> cloned_substates;
    for(auto& current_substate : substates) {
        cloned_substates.push_back(current_substate->clone());
    }
    return cloned_substates;
}

State* OrthState::clone(){
    DEBUG("Warning, function of abstract class OrthState::clone() is called.");
    return nullptr;
}


void OrthState::spawn_orthogonal_state(State* input_state) {
    substates.push_back(input_state);
    input_state->entry();
}

std::string OrthState::get_current_state() {
    std::string appended_string;
    bool first = true; // To avoid leading space
    for(auto& current_substate : substates) {
        if(!first) {
            appended_string += " "; // Add space between substates
        }
        appended_string += current_substate->get_current_state();
        first = false;
    }
    return appended_string;
}

//================================================ internal events ================================================

State* OrthState::timer(TIMER_ID id) {
    for(auto& current_substate : substates) {
        State* newSubstate = current_substate->timer(id);
        if(newSubstate != nullptr) {
            // there is substate change, change only the substate
            current_substate->exit();
            delete current_substate;
            current_substate = newSubstate;
            current_substate->entry();
        }
    }
    return nullptr;
}

State* OrthState::sort_out() {
    return handle_event_using_function(&State::sort_out);
}

State* OrthState::sort_out_fbm2() {
    return handle_event_using_function(&State::sort_out_fbm2);
}

State *OrthState::check_piece() {
    return handle_event_using_function(&State::check_piece);
}

State *OrthState::let_through() {
    return handle_event_using_function(&State::let_through);
}

State *OrthState::reset_to_flat() {
    return handle_event_using_function(&State::reset_to_flat);
}

State *OrthState::reset_to_tall() {
    return handle_event_using_function(&State::reset_to_tall);
}
State *OrthState::reset_to_tall_w_metal() {
    return handle_event_using_function(&State::reset_to_tall_w_metal);
}


//================================================ external events ================================================


State* OrthState::laser_front_blocked() {
    return handle_event_using_function(&State::laser_front_blocked);
}

State* OrthState::laser_front_unblocked() {
    return handle_event_using_function(&State::laser_front_unblocked);
}

State* OrthState::laser_back_blocked() {
    return handle_event_using_function(&State::laser_back_blocked);
}

State* OrthState::laser_back_unblocked() {
    return handle_event_using_function(&State::laser_back_unblocked);
}

State* OrthState::button_start_pressed() {
    return handle_event_using_function(&State::button_start_pressed);
}

State* OrthState::button_start_released() {
    return handle_event_using_function(&State::button_start_released);
}

State* OrthState::button_stop_pressed() {
    return handle_event_using_function(&State::button_stop_pressed);
}

State* OrthState::button_stop_released() {
    return handle_event_using_function(&State::button_stop_released);
}

State* OrthState::button_reset_pressed() {
    return handle_event_using_function(&State::button_reset_pressed);
}

State* OrthState::button_reset_released() {
    return handle_event_using_function(&State::button_reset_released);
}

State* OrthState::button_estop_pressed() {
    return handle_event_using_function(&State::button_estop_pressed);
}

State* OrthState::button_estop_released() {
    return handle_event_using_function(&State::button_estop_released);
}

State* OrthState::metal_detected() {
    return handle_event_using_function(&State::metal_detected);
}

State* OrthState::metal_not_detected() {
    return handle_event_using_function(&State::metal_not_detected);
}

State* OrthState::laser_sorting_gate_blocked() {
    return handle_event_using_function(&State::laser_sorting_gate_blocked);
}

State* OrthState::laser_sorting_gate_unblocked() {
    return handle_event_using_function(&State::laser_sorting_gate_unblocked);
}

State* OrthState::laser_ramp_blocked() {
    return handle_event_using_function(&State::laser_ramp_blocked);
}

State* OrthState::laser_ramp_unblocked() {
    return handle_event_using_function(&State::laser_ramp_unblocked);
}

State* OrthState::adc_top_area_blocked() {
    return handle_event_using_function(&State::adc_top_area_blocked);
}

State* OrthState::adc_top_area_unblocked() {
    return handle_event_using_function(&State::adc_top_area_unblocked);
}

State* OrthState::adc_side_area_blocked() {
    return handle_event_using_function(&State::adc_side_area_blocked);
}

State* OrthState::adc_side_area_unblocked() {
    return handle_event_using_function(&State::adc_side_area_unblocked);
}

State* OrthState::adc_calibration_done() {
    return handle_event_using_function(&State::adc_calibration_done);
}


State* OrthState::com_button_estop_pressed() {
    return handle_event_using_function(&State::com_button_estop_pressed);
}

State* OrthState::com_button_estop_released() {
    return handle_event_using_function(&State::com_button_estop_released);
}

State* OrthState::is_pusher() {
    return handle_event_using_function(&State::is_pusher);
}

State* OrthState::is_switch() {
    return handle_event_using_function(&State::is_switch);
}