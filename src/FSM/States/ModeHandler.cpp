#include "ModeHandler.h"

//================================================= constructors & destructors =================================================
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

I_State* ModeHandler::button_estop_pressed(){
    return new EStopViaLocal(data);
}

I_State* ModeHandler::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}

