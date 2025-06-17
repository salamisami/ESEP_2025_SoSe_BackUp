#include "PieceAtADCCRF.h"

//================================================= constructors & destructors =================================================
PieceAtADCCRF::PieceAtADCCRF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtADCCRF::~PieceAtADCCRF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtADCCRF::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
}

void PieceAtADCCRF::exit(){
	PRINT_STATE;
}

State* PieceAtADCCRF::laser_sorting_gate_blocked(){
	return new GateToRamp(data);
}