#include "EndToGateCRS.h"


//================================================= constructors & destructors =================================================
EndToGateCRS::EndToGateCRS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

EndToGateCRS::~EndToGateCRS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void EndToGateCRS::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_LEFT_START);
	int time_required = data->timeprofile_slow.timestamp[(int) Timestamp::END] - data->timeprofile_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
	time_required *= ENDTOGATE_MULTIPLIER;
	data->timer->start_timer(time_required , TIMER_ID::CAL_GATE_RAMP1);
}

void EndToGateCRS::exit(){
	PRINT_STATE;
}

State* EndToGateCRS::timer(TIMER_ID id){
	if(id == TIMER_ID::CAL_GATE_RAMP1){
		return new OpenGateCRS(data);
	}
	return nullptr;
}