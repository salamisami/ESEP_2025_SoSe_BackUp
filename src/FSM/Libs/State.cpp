#include "State.h"

//================================================= constructors & destructors =================================================
State::State(ContextData* data) : data(data) {
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

//===================================================== private functions =====================================================

void State::entry() {
    DEBUG("Warning, function of abstract class entry() is called.");
}

void State::exit() {
    DEBUG("Warning, function of abstract class exit() is called.");
}

std::string State::demangle(const char* mangled) {
    int status;
    char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
    std::string result = (status == 0) ? demangled : mangled;
    free(demangled);
    return result;
}



//===================================================== public functions =====================================================

//TODO this is the problem of the deep history
State* State::clone() {
    DEBUG("Warning, function of abstract class clone() is called.");
    return nullptr;
}

std::string State::get_current_state() {
    const char* state_name = typeid(*this).name();
    return demangle(state_name);
}

State* State::timer(TIMER_ID id) {
    return nullptr;
}

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

State* State::adc_side_area_blocked() {
    return nullptr;
}

State* State::adc_side_area_unblocked() {
    return nullptr;
}

State* State::com_button_estop_pressed() {
    return nullptr;
}

State* State::com_button_estop_released() {
    return nullptr;
}

State* State::adc_calibration_done() {
    return nullptr;
}

State* State::is_pusher() {
    return nullptr;
}

State* State::is_switch() {
    return nullptr;
}