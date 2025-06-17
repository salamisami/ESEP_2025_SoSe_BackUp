#include "GateToRamp.h"

//================================================= constructors & destructors =================================================
GateToRamp::GateToRamp(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

GateToRamp::~GateToRamp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateToRamp::entry(){
	PRINT_STATE;
	
}

void GateToRamp::exit(){
	PRINT_STATE;
	data->timeprofile.timestamp[(int)Timestamp::LASER_RAMP_BLOCKED] = data->stopwatch.peek_time();
}

State* GateToRamp::laser_ramp_blocked(){
	return new ReadyForCDS(data);
}