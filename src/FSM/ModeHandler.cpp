#include "ModeHandler.h"

//================================================= contructors & destructors =================================================
ModeHandler::ModeHandler(ContextData* data, State* previousState) : State(data){
    if(previousState == nullptr) {
        substate = new Idle(data);
    } else {
        substate = previousState;
    }
    
}

ModeHandler::~ModeHandler() {}

//===================================================== private functions =====================================================

void ModeHandler::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->entry();
}

void ModeHandler::exit() {
    substate->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//===================================================== public functions =====================================================

State* ModeHandler::button_start_pressed(){
    State* newSubstate = substate->button_start_pressed();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

State* ModeHandler::button_start_released(){
    State* newSubstate = substate->button_start_released();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

State* ModeHandler::button_stop_pressed(){
    State* newSubstate = substate->button_stop_pressed();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

State* ModeHandler::button_estop_pressed(){
    return new Error(data);

}

State* ModeHandler::timer(int id){
    State* newSubstate = substate->timer(id);
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

State* ModeHandler::laser_front_blocked(){
    State* newSubstate = substate->laser_front_blocked();
    if(newSubstate != nullptr){
        //there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

State* ModeHandler::adc_calibration_done(){
    State* newSubstate = substate->adc_calibration_done();
    if(newSubstate != nullptr){
        //there is substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}

