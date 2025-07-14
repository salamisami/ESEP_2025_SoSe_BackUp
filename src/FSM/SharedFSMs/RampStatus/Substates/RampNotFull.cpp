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
    
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RAMP_NOT_FULL);
    //HState::entry();
}

void RampNotFull::exit(){
    //HState::exit();
    
	PRINT_STATE;
}

State* RampNotFull::laser_ramp_blocked()
{
    return new RampTimer(data);
}

State* RampNotFull::clone() {
    return new RampNotFull(data);
}