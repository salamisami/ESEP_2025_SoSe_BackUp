#include "PieceAtGateCRF.h"

//================================================= constructors & destructors =================================================
PieceAtGateCRF::PieceAtGateCRF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtGateCRF::~PieceAtGateCRF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtGateCRF::entry(){
	PRINT_STATE;
}

void PieceAtGateCRF::exit(){
	PRINT_STATE;
}

State* PieceAtGateCRF::adc_top_area_blocked(){
	return new PieceAtADCCRF(data)
;}

State* PieceAtGateCRF::clone() {
	return new PieceAtGateCRF(data);
}