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
	data->stopwatch.start();
	
}

void GateToRampCRF::exit(){
	PRINT_STATE;
	long ramp_duration = data->stopwatch.stop();
	long ramp_timestamp = data->timeprofile.timestamp[(int)Timestamp::LASER_GATE_BLOCKED] + ramp_duration;
	data->timeprofile.timestamp[(int)Timestamp::LASER_RAMP_BLOCKED] = ramp_timestamp;
}

State* GateToRampCRF::laser_ramp_blocked(){
	return new ReadyForCDS(data);
}