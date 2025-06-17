#include "SendToRamp.h"

//================================================= constructors & destructors =================================================
SendToRamp::SendToRamp(ContextData* data) : HState(data, new IdleGateCP(data)) {
    //substate = new SubState(data);
}

SendToRamp::~SendToRamp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SendToRamp::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    HState::entry();
}

void SendToRamp::exit(){
    HState::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}