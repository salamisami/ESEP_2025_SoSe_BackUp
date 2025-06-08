#include "ModeHandler.h"

//================================================= contructors & destructors =================================================
ModeHandler::ModeHandler(ContextData* data, State* initial_substate) : State(data){
    if(initial_substate == nullptr) {
        substate = new Idle(data);
    } else {
        substate = initial_substate;
    }
    
}

ModeHandler::~ModeHandler() {}

//===================================================== private functions =====================================================

void ModeHandler::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    State::entry();
}

void ModeHandler::exit() {
    State::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//===================================================== public functions =====================================================

State* ModeHandler::button_estop_pressed(){
    return new Error(data);
}

