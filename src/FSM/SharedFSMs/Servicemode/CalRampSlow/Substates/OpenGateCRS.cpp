#include "OpenGateCRS.h"

//================================================= constructors & destructors =================================================
OpenGateCRS::OpenGateCRS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

OpenGateCRS::~OpenGateCRS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateCRS::entry(){
	PRINT_STATE;
	if(data->is_switch){
		data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
	}
	
	data->timer->start_timer(OPEN_GATE_SLOW_DURATION, TIMER_ID::CAL_GATE_RAMP2);
}

void OpenGateCRS::exit(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* OpenGateCRS::timer(TIMER_ID id){
	if(id == TIMER_ID::CAL_GATE_RAMP2){
		return new PieceAtGateCRS(data);
	}
	return nullptr;
}

State* OpenGateCRS::clone() {
	return new OpenGateCRS(data);
}