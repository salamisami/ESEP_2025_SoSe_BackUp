#include "RampFull.h"


//================================================= constructors & destructors =================================================
RampFull::RampFull(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

RampFull::~RampFull() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampFull::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RAMP_FULL);
}

void RampFull::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* RampFull::laser_ramp_unblocked()
{
    return new RampNotFull(data);
}

State* RampFull::clone() {
    return new RampFull(data);
}