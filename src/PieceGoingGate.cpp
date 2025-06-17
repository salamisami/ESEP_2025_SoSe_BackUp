#include "PieceGoingGate.h"

//================================================= constructors & destructors =================================================
PieceGoingGate::PieceGoingGate(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingGate::~PieceGoingGate() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingGate::entry(){
	PRINT_STATE
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_LEFT_START);
	data->timer->start_timer(1500, TIMER_ID::CalGateRamp1);
}

void PieceGoingGate::exit(){
	PRINT_STATE
}

State* PieceGoingGate::timer(TIMER_ID id){
	if(id == TIMER_ID::CalGateRamp1){
		return new PieceGoingGateBackward(data);
	}
	return nullptr;
}