#include "PieceGoingToGate.h"

//================================================= constructors & destructors =================================================
PieceGoingToGate::PieceGoingToGate(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingToGate::~PieceGoingToGate() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingToGate::entry(){
	PRINT_STATE
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
}

void PieceGoingToGate::exit(){
	PRINT_STATE
}

State* PieceGoingToGate::laser_sorting_gate_blocked(){
	return new PieceAtGate(data);
}