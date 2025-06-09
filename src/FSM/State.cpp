#include "State.h"

//================================================= contructors & destructors =================================================
State::State(ContextData* data)
    : data(data)
    , substate(nullptr) {
    //std::cout << "State Constructor" << std::endl;
}

//copy constructor
// State::State(const State& other) {
//     if(other.substate != nullptr){
//         this->substate = new State(*other.substate);
//     } else {
//         this->substate = nullptr;
//     }
//     this->data = other.data;
//     //std::cout << "copy constructor called." << std::endl;
// }

State::~State() {
    //std::cout << "State Destructor" << std::endl;
    if(substate != nullptr) {
        delete substate;
    }
}

//===================================================== private functions =====================================================

I_State* State::handle_event_using_function(I_State* (I_State::* handler_function)()) {
    if(substate == nullptr) {
        return nullptr;
    }
    I_State* newSubstate = (substate->*handler_function)();
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
// I_State* StateA::estop_pressed() {
//     I_State* clone_substate = substate->clone();
//     data->stateStack->push(clone_substate);
//     return new EmergencyStop(data);
// }

//load history
// I_State* EmergencyStop::estop_released() {
//     I_State* loaded_state = data->stateStack->top();
//     data->stateStack->pop();
//     return new StateA(data, loaded_state);
// }

//outside loop
// I_State* StateA::restart(){
//     return new StateA(data);
// }

//inside loop
// I_State* StateA::tick() {
//     super_State::exit();
//     super_State::entry();
//     return nullptr;
// }

//explicit entry
// I_State* StateA::service() {
//      I_State* initial_explicit_substate = new StartEngine(data);
//      return new StartCar(data, initial_explicit_substate);
// }

//explicit exit
// I_State* StateA::service() {
//     I_State* newSubstate = substate->service();
//     if(newSubstate != nullptr) {
//         return newSubstate;
//     }
//     return nullptr;
// }



//===================================================== public functions =====================================================

void State::entry() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->entry();
}

void State::exit() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->exit();
}


State* State::clone(){
    State* clonedState = new State(data);
    if(substate != nullptr){
        clonedState->substate = substate->clone();
    } else {
        clonedState->substate = nullptr;
    }
    return clonedState;
}

I_State* State::timer(int id) {
    if(substate == nullptr) {
        return nullptr;
    }
    I_State* newSubstate = substate->timer(id);
    if(newSubstate != nullptr) {
        // there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}


I_State* State::laser_front_blocked() {
    return handle_event_using_function(&I_State::laser_front_blocked);
}

I_State* State::laser_front_unblocked() {
    return handle_event_using_function(&I_State::laser_front_unblocked);
}

I_State* State::laser_back_blocked() {
    return handle_event_using_function(&I_State::laser_back_blocked);
}

I_State* State::laser_back_unblocked() {
    return handle_event_using_function(&I_State::laser_back_unblocked);
}

I_State* State::button_start_pressed() {
    return handle_event_using_function(&I_State::button_start_pressed);
}

I_State* State::button_start_released() {
    return handle_event_using_function(&I_State::button_start_released);
}

I_State* State::button_stop_pressed() {
    return handle_event_using_function(&I_State::button_stop_pressed);
}

I_State* State::button_stop_released() {
    return handle_event_using_function(&I_State::button_stop_released);
}

I_State* State::button_reset_pressed() {
    return handle_event_using_function(&I_State::button_reset_pressed);
}

I_State* State::button_reset_released() {
    return handle_event_using_function(&I_State::button_reset_released);
}

I_State* State::button_estop_pressed() {
    return handle_event_using_function(&I_State::button_estop_pressed);
}

I_State* State::button_estop_released() {
    return handle_event_using_function(&I_State::button_estop_released);
}

I_State* State::metal_detected() {
    return handle_event_using_function(&I_State::metal_detected);
}

I_State* State::metal_not_detected() {
    return handle_event_using_function(&I_State::metal_not_detected);
}

I_State* State::laser_sorting_gate_blocked() {
    return handle_event_using_function(&I_State::laser_sorting_gate_blocked);
}

I_State* State::laser_sorting_gate_unblocked() {
    return handle_event_using_function(&I_State::laser_sorting_gate_unblocked);
}

I_State* State::laser_ramp_blocked() {
    return handle_event_using_function(&I_State::laser_ramp_blocked);
}

I_State* State::laser_ramp_unblocked() {
    return handle_event_using_function(&I_State::laser_ramp_unblocked);
}

I_State* State::adc_top_area_blocked() {
    return handle_event_using_function(&I_State::adc_top_area_blocked);
}

I_State* State::adc_top_area_unblocked() {
    return handle_event_using_function(&I_State::adc_top_area_unblocked);
}

I_State* State::adc_side_area_blocked() {
    return handle_event_using_function(&I_State::adc_side_area_blocked);
}

I_State* State::adc_side_area_unblocked() {
    return handle_event_using_function(&I_State::adc_side_area_unblocked);
}

I_State* State::adc_calibration_done() {
    return handle_event_using_function(&I_State::adc_calibration_done);
}

I_State* State::adc_new_piece() {
    return handle_event_using_function(&I_State::adc_new_piece);
}