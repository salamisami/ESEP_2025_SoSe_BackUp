#include "HState.h"

//================================================= constructors & destructors =================================================
HState::HState(ContextData* data)
    : State(data)
    , substate(nullptr) {
    //std::cout << "HState Constructor" << std::endl;
}

//copy constructor
// HState::HState(const HState& other) {
//     if(other.substate != nullptr){
//         this->substate = new HState(*other.substate);
//     } else {
//         this->substate = nullptr;
//     }
//     this->data = other.data;
//     //std::cout << "copy constructor called." << std::endl;
// }

HState::~HState() {
    //std::cout << "HState Destructor" << std::endl;
    if(substate != nullptr) {
        delete substate;
    }
}

//===================================================== private functions =====================================================

State* HState::handle_event_using_function(State* (State::* handler_function)()) {
    if(substate == nullptr) {
        return nullptr;
    }
    State* newSubstate = (substate->*handler_function)();
    if(newSubstate != nullptr) {
        // there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

//save history
// State* StateA::estop_pressed() {
//     State* cloned_state = clone();
//     data->stateStack->push(cloned_substate);
//     return new EmergencyStop(data);
// }

//load history
// State* EmergencyStop::estop_released() {
//     State* loaded_state = data->stateStack->top();
//     data->stateStack->pop();
//     if(loaded_state != nullptr){
//         return loaded_state;
//     }
//     return StateA(data);
// }

//outside loop
// State* StateA::restart(){
//     return new StateA(data);
// }

//inside loop
// State* StateA::tick() {
//     super_State::exit();
//     super_State::entry();
//     return nullptr;
// }

//explicit entry
// State* StateA::service() {
//      State* initial_explicit_substate = new StartEngine(data);
//      return new StartCar(data, initial_explicit_substate);
// }

//explicit exit
// State* StateA::service() {
//     State* newSubstate = substate->service();
//     if(newSubstate != nullptr) {
//         return newSubstate;
//     }
//     return nullptr;
// }



//===================================================== public functions =====================================================

void HState::entry() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->entry();
}

void HState::exit() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->exit();
}


HState* HState::clone(){
    HState* clonedState = new HState(data);
    if(substate != nullptr){
        clonedState->substate = substate->clone();
    } else {
        clonedState->substate = nullptr;
    }
    return clonedState;
}

State* HState::timer(TIMER_ID id) {
    if(substate == nullptr) {
        return nullptr;
    }
    State* newSubstate = substate->timer(id);
    if(newSubstate != nullptr) {
        // there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}


State* HState::laser_front_blocked() {
    return handle_event_using_function(&State::laser_front_blocked);
}

State* HState::laser_front_unblocked() {
    return handle_event_using_function(&State::laser_front_unblocked);
}

State* HState::laser_back_blocked() {
    return handle_event_using_function(&State::laser_back_blocked);
}

State* HState::laser_back_unblocked() {
    return handle_event_using_function(&State::laser_back_unblocked);
}

State* HState::button_start_pressed() {
    return handle_event_using_function(&State::button_start_pressed);
}

State* HState::button_start_released() {
    return handle_event_using_function(&State::button_start_released);
}

State* HState::button_stop_pressed() {
    return handle_event_using_function(&State::button_stop_pressed);
}

State* HState::button_stop_released() {
    return handle_event_using_function(&State::button_stop_released);
}

State* HState::button_reset_pressed() {
    return handle_event_using_function(&State::button_reset_pressed);
}

State* HState::button_reset_released() {
    return handle_event_using_function(&State::button_reset_released);
}

State* HState::button_estop_pressed() {
    return handle_event_using_function(&State::button_estop_pressed);
}

State* HState::button_estop_released() {
    return handle_event_using_function(&State::button_estop_released);
}

State* HState::metal_detected() {
    return handle_event_using_function(&State::metal_detected);
}

State* HState::metal_not_detected() {
    return handle_event_using_function(&State::metal_not_detected);
}

State* HState::laser_sorting_gate_blocked() {
    return handle_event_using_function(&State::laser_sorting_gate_blocked);
}

State* HState::laser_sorting_gate_unblocked() {
    return handle_event_using_function(&State::laser_sorting_gate_unblocked);
}

State* HState::laser_ramp_blocked() {
    return handle_event_using_function(&State::laser_ramp_blocked);
}

State* HState::laser_ramp_unblocked() {
    return handle_event_using_function(&State::laser_ramp_unblocked);
}

State* HState::adc_top_area_blocked() {
    return handle_event_using_function(&State::adc_top_area_blocked);
}

State* HState::adc_top_area_unblocked() {
    return handle_event_using_function(&State::adc_top_area_unblocked);
}

State* HState::adc_side_area_blocked() {
    return handle_event_using_function(&State::adc_side_area_blocked);
}

State* HState::adc_side_area_unblocked() {
    return handle_event_using_function(&State::adc_side_area_unblocked);
}

State* HState::com_button_estop_pressed() {
    return handle_event_using_function(&State::com_button_estop_pressed);
}

State* HState::com_button_estop_released() {
    return handle_event_using_function(&State::com_button_estop_released);
}

State* HState::adc_calibration_done() {
    return handle_event_using_function(&State::adc_calibration_done);
}

State* HState::adc_new_piece() {
    return handle_event_using_function(&State::adc_new_piece);
}

State* HState::is_pusher(){
    return handle_event_using_function(&State::is_pusher);
}

State* HState::is_switch(){
    return handle_event_using_function(&State::is_switch);
}