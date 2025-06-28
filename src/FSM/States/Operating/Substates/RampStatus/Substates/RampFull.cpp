#include "RampFull.h"
#include "RampNotFull.h"


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
    data->sender->send_event(Topic::INTERNAL, Internal_Enum::RAMP_FULL);
}

void RampFull::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* laser_ramp_blocked()
{
    return new RampNotFull(data);
}