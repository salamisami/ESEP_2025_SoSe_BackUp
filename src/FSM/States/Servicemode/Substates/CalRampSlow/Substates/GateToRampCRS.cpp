#include "GateToRampCRS.h"

//================================================= constructors & destructors =================================================
GateToRampCRS::GateToRampCRS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

GateToRampCRS::~GateToRampCRS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateToRampCRS::entry(){
	PRINT_STATE;
	data->stopwatch.start();
	
}

void GateToRampCRS::exit(){
	PRINT_STATE;
	long ramp_duration = data->stopwatch.stop();
	long ramp_timestamp = data->timeprofile_slow.timestamp[(int)Timestamp::LASER_GATE_BLOCKED] + ramp_duration;
	data->timeprofile_slow.timestamp[(int)Timestamp::LASER_RAMP_BLOCKED] = ramp_timestamp;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
}

State* GateToRampCRS::laser_ramp_blocked(){
	return new CalibrationFinished(data);
}