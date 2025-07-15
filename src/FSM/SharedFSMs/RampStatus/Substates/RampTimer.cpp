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
    
    data->timer->start_timer(RAMP_FULL_TIMER, TIMER_ID::RAMP_TIMER);
}

void RampTimer::exit(){
    
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

State* RampTimer::clone() {
    return new RampTimer(data);
}