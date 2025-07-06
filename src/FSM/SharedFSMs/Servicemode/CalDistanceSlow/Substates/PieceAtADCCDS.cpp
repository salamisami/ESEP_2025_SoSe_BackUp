#include "PieceAtADCCDS.h"

//================================================= constructors & destructors =================================================
PieceAtADCCDS::PieceAtADCCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtADCCDS::~PieceAtADCCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtADCCDS::entry(){
	PRINT_STATE;
	data->timeprofile.slow_timestamps[(int)Timestamp::ADC_BLOCKED] = data->stopwatch.peek_time();
}

void PieceAtADCCDS::exit(){
	PRINT_STATE;
}

State* PieceAtADCCDS::adc_top_area_unblocked(){
	return new ADCToGateCDS(data);
}

State* PieceAtADCCDS::clone() {
	return new PieceAtADCCDS(data);
}