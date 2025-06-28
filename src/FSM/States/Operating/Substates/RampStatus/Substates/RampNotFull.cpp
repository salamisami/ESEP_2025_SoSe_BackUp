#include "RampNotFull.h"
#include "RampTimer.h"
#include "HState.h"



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
    data->sender->send_event(Topic::INTERNAL, INTERNAL_Enum::RAMP_NOT_FULL);
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