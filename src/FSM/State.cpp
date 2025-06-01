#include "State.h"

//================================================= contructors & destructors =================================================
State::State(ContextData* data)
    : data(data)
    , substate(nullptr){
    //std::cout << "State Constructor" << std::endl;
}

//copy constructor
State::State(const State& other) {
    if(other.substate != nullptr){
        this->substate = new State(*other.substate);
    } else {
        this->substate = nullptr;
    }
    this->data = other.data;
    //std::cout << "copy constructor called." << std::endl;
}

State::~State() {
    //std::cout << "State Destructor" << std::endl;
    if(substate != nullptr){
        delete substate;
    }
}

//===================================================== private functions =====================================================

State* State::handle_event_using_function(State* (State::* handler_function)()) {
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
//     State* clone_substate = new State(*substate);
//     data->stateStack->push(clone_substate);
//     return new EmergencyStop(data);
// }

//load history
// State* EmergencyStop::estop_released() {
//     State* loaded_state = data->stateStack->top();
//     data->stateStack->pop();
//     return new StateA(data, loaded_state);
// }

//outside loop
// State* StateA::restart(){
//     return new StateA(data);
// }

//inside loop
// State* StateA::tick() {
//     super_substate->exit();
//     super_substate->entry();
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

void State::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void State::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* State::timer(int id) {
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


State* State::laser_front_blocked() {
    return handle_event_using_function(&State::laser_front_blocked);
}

State* State::laser_front_unblocked() {
    return handle_event_using_function(&State::laser_front_unblocked);
}

State* State::laser_back_blocked() {
    return handle_event_using_function(&State::laser_back_blocked);
}

State* State::laser_back_unblocked() {
    return handle_event_using_function(&State::laser_back_unblocked);
}

State* State::button_start_pressed() {
    return handle_event_using_function(&State::button_start_pressed);
}

State* State::button_start_released() {
    return handle_event_using_function(&State::button_start_released);
}

State* State::button_stop_pressed() {
    return handle_event_using_function(&State::button_stop_pressed);
}

State* State::button_stop_released() {
    return handle_event_using_function(&State::button_stop_released);
}

State* State::button_reset_pressed() {
    return handle_event_using_function(&State::button_reset_pressed);
}

State* State::button_reset_released() {
    return handle_event_using_function(&State::button_reset_released);
}

State* State::button_estop_pressed() {
    return handle_event_using_function(&State::button_estop_pressed);
}

State* State::button_estop_released() {
    return handle_event_using_function(&State::button_estop_released);
}

State* State::metal_detected() {
    return handle_event_using_function(&State::metal_detected);
}

State* State::metal_not_detected() {
    return handle_event_using_function(&State::metal_not_detected);
}

State* State::laser_sorting_gate_blocked() {
    return handle_event_using_function(&State::laser_sorting_gate_blocked);
}

State* State::laser_sorting_gate_unblocked() {
    return handle_event_using_function(&State::laser_sorting_gate_unblocked);
}

State* State::laser_ramp_blocked() {
    return handle_event_using_function(&State::laser_ramp_blocked);
}

State* State::laser_ramp_unblocked() {
    return handle_event_using_function(&State::laser_ramp_unblocked);
}

State* State::adc_top_area_blocked() {
    return handle_event_using_function(&State::adc_top_area_blocked);
}

State* State::adc_top_area_unblocked() {
    return handle_event_using_function(&State::adc_top_area_unblocked);
}

State* State::adc_side_area_blocked() {
    return handle_event_using_function(&State::adc_side_area_blocked);
}

State* State::adc_side_area_unblocked() {
    return handle_event_using_function(&State::adc_side_area_unblocked);
}

State* State::adc_calibration_done() {
    return handle_event_using_function(&State::adc_calibration_done);
}

State* State::adc_new_piece() {
    return handle_event_using_function(&State::adc_new_piece);
}