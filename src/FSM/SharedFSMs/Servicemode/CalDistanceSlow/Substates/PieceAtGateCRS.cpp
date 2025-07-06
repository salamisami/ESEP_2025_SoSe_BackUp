#include "PieceAtGateCRS.h"

//================================================= constructors & destructors =================================================
PieceAtGateCRS::PieceAtGateCRS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtGateCRS::~PieceAtGateCRS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtGateCRS::entry(){
	PRINT_STATE;
}

void PieceAtGateCRS::exit(){
	PRINT_STATE;
}

State* PieceAtGateCRS::adc_top_area_blocked(){
	return new PieceAtADCCRS(data)
;}

State* PieceAtGateCRS::clone() {
	return new PieceAtGateCRS(data);
}