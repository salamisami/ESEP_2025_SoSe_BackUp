#include "ModeHandler.h"

//================================================= contructors & destructors =================================================
ModeHandler::ModeHandler(ContextData* data, State* previousState) : State(data){
    if(previousState == nullptr) {
        subState = new Idle(data);
    } else {
        subState = previousState;
    }
    
}

ModeHandler::~ModeHandler() {}

//===================================================== private functions =====================================================

void ModeHandler::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    subState->entry();
}

void ModeHandler::exit() {
    subState->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//===================================================== public functions =====================================================

State* ModeHandler::button_start_pressed(){
    State* newSubstate = subState->button_start_pressed();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}

State* ModeHandler::button_start_released(){
    State* newSubstate = subState->button_start_released();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}

State* ModeHandler::button_stop_pressed(){
    State* newSubstate = subState->button_stop_pressed();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}

State* ModeHandler::button_estop_pressed(){
    return new Error(data);

}

State* ModeHandler::timer(int id){
    State* newSubstate = subState->timer(id);
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}


