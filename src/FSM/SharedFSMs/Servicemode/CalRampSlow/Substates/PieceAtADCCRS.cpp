#include "PieceAtADCCRS.h"

//================================================= constructors & destructors =================================================
PieceAtADCCRS::PieceAtADCCRS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtADCCRS::~PieceAtADCCRS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtADCCRS::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
}

void PieceAtADCCRS::exit(){
	PRINT_STATE;
}

State* PieceAtADCCRS::laser_sorting_gate_blocked(){
	return new GateToRampCRS(data);
}