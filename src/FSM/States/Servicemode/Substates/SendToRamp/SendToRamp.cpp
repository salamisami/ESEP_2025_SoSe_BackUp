#include "SendToRamp.h"

//================================================= constructors & destructors =================================================
SendToRamp::SendToRamp(ContextData* data) : HState(data, new IdleGateCP(data)) {
    //substate = new SubState(data);
}

SendToRamp::~SendToRamp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SendToRamp::entry(){
	PRINT_STATE
    HState::entry();
}

void SendToRamp::exit(){
    HState::exit();
    PRINT_STATE
}