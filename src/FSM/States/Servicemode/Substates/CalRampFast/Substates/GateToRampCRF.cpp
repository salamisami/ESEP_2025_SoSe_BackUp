#include "GateToRampCRF.h"

//================================================= constructors & destructors =================================================
GateToRampCRF::GateToRampCRF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

GateToRampCRF::~GateToRampCRF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateToRampCRF::entry(){
	PRINT_STATE;
	
}

void GateToRampCRF::exit(){
	PRINT_STATE;
	data->timeprofile.timestamp[(int)Timestamp::LASER_RAMP_BLOCKED] = data->stopwatch.peek_time();
}

State* GateToRampCRF::laser_ramp_blocked(){
	return new ReadyForCDS(data);
}