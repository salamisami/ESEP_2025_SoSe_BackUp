#include "ModeHandler.h"

//================================================= constructors & destructors =================================================
ModeHandler::ModeHandler(ContextData* data, HState* initial_substate) : HState(data){
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
    HState::entry();
}

void ModeHandler::exit() {
    HState::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//===================================================== public functions =====================================================

State* ModeHandler::button_estop_pressed(){
    return new EStopViaLocal(data);
}

State* ModeHandler::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}

