#include "EndToGateCRF.h"


//================================================= constructors & destructors =================================================
EndToGateCRF::EndToGateCRF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

EndToGateCRF::~EndToGateCRF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void EndToGateCRF::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_LEFT_START);
	int time_required = data->timeprofile.fast_timestamps[(int) Timestamp::END] - data->timeprofile.fast_timestamps[(int) Timestamp::LASER_GATE_UNBLOCKED];
	time_required = (double) time_required * ENDTOGATE_MULTIPLIER;
	data->timer->start_timer(time_required, TIMER_ID::CAL_GATE_RAMP1);
}

void EndToGateCRF::exit(){
	PRINT_STATE;
}

State* EndToGateCRF::timer(TIMER_ID id){
	if(id == TIMER_ID::CAL_GATE_RAMP1){
		return new OpenGateCRF(data);
	}
	return nullptr;
}

State* EndToGateCRF::clone() {
	return new EndToGateCRF(data);
}