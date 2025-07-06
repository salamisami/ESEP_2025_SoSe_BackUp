#include "RampTimer.h"


//================================================= constructors & destructors =================================================
RampTimer::RampTimer(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

RampTimer::~RampTimer() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RampTimer::entry(){
	PRINT_STATE;
    //TODO CODE
    data->timer->start_timer(1000, TIMER_ID::RAMP_TIMER);
}

void RampTimer::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* RampTimer::laser_ramp_unblocked()
{
    return new RampNotFull(data);
}

State* RampTimer::timer(TIMER_ID id)
{
    if(id == TIMER_ID::RAMP_TIMER) return new RampFull(data);
    return nullptr;
}