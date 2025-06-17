#include "PieceAtADC.h"

//================================================= constructors & destructors =================================================
PieceAtADC::PieceAtADC(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtADC::~PieceAtADC() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtADC::entry(){
	PRINT_STATE;
	data->timeprofile.timestamp[(int)Timestamp::ADC_BLOCKED] = data->stopwatch.peek_time();
}

void PieceAtADC::exit(){
	PRINT_STATE;
}

State* PieceAtADC::adc_top_area_unblocked(){
	return new PieceGoingToSG(data);
}