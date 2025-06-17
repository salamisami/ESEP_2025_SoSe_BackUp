#include "PieceGoingGateBackward.h"

//================================================= constructors & destructors =================================================
PieceGoingGateBackward::PieceGoingGateBackward(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingGateBackward::~PieceGoingGateBackward() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingGateBackward::entry(){
	PRINT_STATE
	if(data->is_switch){
		data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
	}
	
	//TODO magic number
	data->timer->start_timer(600, TIMER_ID::CalGateRamp2);
}

void PieceGoingGateBackward::exit(){
	PRINT_STATE
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* PieceGoingGateBackward::timer(TIMER_ID id){
	if(id == TIMER_ID::CalGateRamp2){
		return new PieceGoingToADCBackward(data);
	}
	return nullptr;
}

State* PieceGoingGateBackward::laser_sorting_gate_blocked(){
	return new PieceGoingToADCBackward(data);
}