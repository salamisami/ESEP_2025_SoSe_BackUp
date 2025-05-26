#include "State.h"

//================================================= contructors & destructors =================================================
State::State(ContextData* data)
    : data(data) {
    //std::cout << "State Constructor" << std::endl;

}

State::~State() {
    //std::cout << "State Destructor" << std::endl;
    //delete stateStack;
}

//===================================================== private functions =====================================================

//void State::privateFunction(){}

//===================================================== public functions =====================================================

State* State::laser_front_blocked() {
    return nullptr;
}

State* State::laser_front_unblocked() {
    return nullptr;
}

State* State::laser_back_blocked() {
    return nullptr;
}

State* State::laser_back_unblocked() {
    return nullptr;
}

State* State::button_start_pressed() {
    return nullptr;
}

State* State::button_start_released() {
    return nullptr;
}

State* State::button_stop_pressed() {
    return nullptr;
}

State* State::button_stop_released() {
    return nullptr;
}

State* State::button_reset_pressed() {
    return nullptr;
}

State* State::button_reset_released() {
    return nullptr;
}

State* State::button_estop_pressed() {
    return nullptr;
}

State* State::button_estop_released() {
    return nullptr;
}

State* State::metal_detected() {
    return nullptr;
}

State* State::metal_not_detected() {
    return nullptr;
}

State* State::laser_sorting_gate_blocked() {
    return nullptr;
}

State* State::laser_sorting_gate_unblocked() {
    return nullptr;
}

State* State::laser_ramp_blocked() {
    return nullptr;
}

State* State::laser_ramp_unblocked() {
    return nullptr;
}

State* State::adc_top_area_blocked() {
    return nullptr;
}

State* State::adc_top_area_unblocked() {
    return nullptr;
}

// State* State::adc_side_area_blocked() {
//     return nullptr;
// }

// State* State::adc_side_area_unblocked() {
//     return nullptr;
// }

State* State::timer(int id) {
    return nullptr;
}