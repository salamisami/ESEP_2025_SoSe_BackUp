#include "RampNotFull.h"



//================================================= constructors & destructors =================================================
RampNotFull::RampNotFull(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

RampNotFull::~RampNotFull() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampNotFull::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RAMP_NOT_FULL);
    //HState::entry();
}

void RampNotFull::exit(){
    //HState::exit();
    //TODO CODE
	PRINT_STATE;
}

State* RampNotFull::laser_ramp_blocked()
{
    return new RampTimer(data);
}