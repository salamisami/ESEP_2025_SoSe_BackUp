#include "ModeHandler.h"

//================================================= constructors & destructors =================================================
ModeHandler::ModeHandler(ContextData* data) : HState(data, new IdleMode(data)){
    
}

ModeHandler::~ModeHandler() {}

//===================================================== private functions =====================================================

void ModeHandler::entry() {
    PRINT_STATE;
    HState::entry();
}

void ModeHandler::exit() {
    HState::exit();
    PRINT_STATE;
}

//===================================================== public functions =====================================================

State* ModeHandler::button_estop_pressed(){
    return new EStopViaLocal(data);
}

State* ModeHandler::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}

