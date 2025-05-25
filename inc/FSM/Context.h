#ifndef CONTEXT_H
#define CONTEXT_H
#pragma once

#include "State.h"
#include "Macros.h"

template<typename T>
class Context {
    static_assert(std::is_base_of<State, T>::value, "Template parameter must inherit from State");
    //============================================ contructors & destructors ============================================
public:
    Context();
    Context(ContextData* data);
    virtual ~Context();

    //================================================ public functions ================================================
public:
    virtual void handleEvent(_pulse event);


    //================================================ private variables ================================================
protected:
    ContextData* data;
    State* state;

    //================================================ private functions ================================================
private:
    //int myVariable

};

//================================================= contructors & destructors =================================================
template <typename T>
Context<T>::Context(){
}
template <typename T>
Context<T>::Context(ContextData* data):state(new T(data)){
    this->data = data;
    state->entry();
}
template <typename T>
Context<T>::~Context() {
    delete state;
}

//===================================================== private functions =====================================================

//void Context<T>::privateFunction(){}

//===================================================== public functions =====================================================
template <typename T>
void Context<T>::handleEvent(_pulse event) {
    State* newState = nullptr;
    Topic event_code = (Topic) event.code;
    InterruptEnum event_value = (InterruptEnum) event.value.sival_int;

    if(event_code == Topic::INTERRUPT){
        switch(event_value) {
        //TODO implement ADC_Enum
        case InterruptEnum::LASER_FRONT_BLOCKED:
            newState = state->laser_front_blocked();
            break;
        case InterruptEnum::LASER_FRONT_UNBLOCKED:
            newState = state->laser_front_unblocked();
            break;
        case InterruptEnum::LASER_BACK_BLOCKED:
            newState = state->laser_back_blocked();
            break;
        case InterruptEnum::LASER_BACK_UNBLOCKED:
            newState = state->laser_back_unblocked();
            break;
        case InterruptEnum::BUTTON_START_PRESSED:
            newState = state->button_start_pressed();
            break;
        case InterruptEnum::BUTTON_START_RELEASED:
            newState = state->button_start_released();
            break;
        case InterruptEnum::BUTTON_STOP_PRESSED:
            newState = state->button_stop_pressed();
            break;
        case InterruptEnum::BUTTON_STOP_RELEASED:
            newState = state->button_stop_released();
            break;
        case InterruptEnum::BUTTON_RESET_PRESSED:
            newState = state->button_reset_pressed();
            break;
        case InterruptEnum::BUTTON_RESET_RELEASED:
            newState = state->button_reset_released();
            break;
        case InterruptEnum::BUTTON_ESTOP_PRESSED:
            newState = state->button_estop_pressed();
            break;
        case InterruptEnum::BUTTON_ESTOP_RELEASED:
            newState = state->button_estop_released();
            break;
        case InterruptEnum::METAL_DETECTED:
            newState = state->metal_detected();
            break;
        case InterruptEnum::METAL_NOT_DETECTED:
            newState = state->metal_not_detected();
            break;
        case InterruptEnum::LASER_SORTING_GATE_BLOCKED:
            newState = state->laser_sorting_gate_blocked();
            break;
        case InterruptEnum::LASER_SORTING_GATE_UNBLOCKED:
            newState = state->laser_sorting_gate_unblocked();
            break;
        case InterruptEnum::LASER_RAMP_BLOCKED:
            newState = state->laser_ramp_blocked();
            break;
        case InterruptEnum::LASER_RAMP_UNBLOCKED:
            newState = state->laser_ramp_unblocked();
            break;
        case InterruptEnum::ADC_TOP_AREA_BLOCKED:
            newState = state->adc_top_area_blocked();
            break;
        case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
            newState = state->adc_top_area_unblocked();
            break;
        // case InterruptEnum::ADC_SIDE_AREA_BLOCKED:
        //     newState = state->adc_side_area_blocked();
        //     break;
        // case InterruptEnum::ADC_SIDE_AREA_UNBLOCKED:
        //     newState = state->adc_side_area_unblocked();
        //     break;

        default:
            break;
        }   
    } else if(event_code == Topic::TIMER){
        newState = state->timer((int) event_value);
    }
    
    if(newState != nullptr) {
        state->exit();
        delete state;
        state = newState;
        state->entry();
    }

}

#endif