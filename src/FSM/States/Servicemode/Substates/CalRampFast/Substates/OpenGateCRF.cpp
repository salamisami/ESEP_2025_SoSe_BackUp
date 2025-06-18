#include "OpenGateCRF.h"

//================================================= constructors & destructors =================================================
OpenGateCRF::OpenGateCRF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

OpenGateCRF::~OpenGateCRF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateCRF::entry(){
	PRINT_STATE;
	if(data->is_switch){
		data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
	}
	
	//TODO magic number
	data->timer->start_timer(600, TIMER_ID::CAL_GATE_RAMP2);
}

void OpenGateCRF::exit(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* OpenGateCRF::timer(TIMER_ID id){
	if(id == TIMER_ID::CAL_GATE_RAMP2){
		return new PieceAtGateCRF(data);
	}
	return nullptr;
}

State* OpenGateCRF::laser_sorting_gate_blocked(){
	return new PieceAtGateCRF(data);
}