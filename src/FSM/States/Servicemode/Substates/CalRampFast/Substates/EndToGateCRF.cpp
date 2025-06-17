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
	int time_required = data->timeprofile.timestamp[(int) Timestamp::END] - data->timeprofile.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
	data->timer->start_timer(time_required + 1000, TIMER_ID::CalGateRamp1);
}

void EndToGateCRF::exit(){
	PRINT_STATE;
}

State* EndToGateCRF::timer(TIMER_ID id){
	if(id == TIMER_ID::CalGateRamp1){
		return new OpenGateCRF(data);
	}
	return nullptr;
}