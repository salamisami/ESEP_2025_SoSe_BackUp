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


OrthState* OrthState::clone() {
    //TODO test and review
    std::vector<State*> cloned_substates;
    for(auto& current_substate : substates) {
        cloned_substates.push_back(current_substate->clone());
    }
    OrthState* cloned_ortho = new OrthState(data, cloned_substates);
    return cloned_ortho;
}

void OrthState::spawn_orthogonal_state(State* input_state){
    substates.push_back(input_state);
    input_state->entry();
}

//TODO how should it behave?
// std::string OrthState::show_state() {
//     for(auto& current_substate : substates) {
        
//     }
//     const char* 
//     return typeid(*this).name();
// }

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

State* OrthState::adc_new_piece() {
    return handle_event_using_function(&State::adc_new_piece);
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