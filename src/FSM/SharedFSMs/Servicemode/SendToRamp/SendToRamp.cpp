#include "SendToRamp.h"

//================================================= constructors & destructors =================================================
SendToRamp::SendToRamp(ContextData* data) : HState(data, new IdleSTR(data)) {
    //substate = new SubState(data);
}

SendToRamp::SendToRamp(ContextData* data, State* initial_substate) : HState(data, initial_substate) 
{}

SendToRamp::~SendToRamp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SendToRamp::entry(){
	PRINT_STATE;
    HState::entry();
}

void SendToRamp::exit(){
    HState::exit();
    PRINT_STATE;
}

State* SendToRamp::clone() {
    return new SendToRamp(data, substate->clone());
}