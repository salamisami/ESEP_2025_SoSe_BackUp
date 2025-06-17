#include "PieceGoingToADC.h"

//================================================= constructors & destructors =================================================
PieceGoingToADCBackward::PieceGoingToADCBackward(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingToADCBackward::~PieceGoingToADCBackward() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingToADCBackward::entry(){
	PRINT_STATE
}

void PieceGoingToADCBackward::exit(){
	PRINT_STATE
}

State* PieceGoingToADCBackward::adc_top_area_blocked(){
	return new PieceGoingToGate(data)
;}