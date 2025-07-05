#include "PieceAtADCCDF.h"

//================================================= constructors & destructors =================================================
PieceAtADCCDF::PieceAtADCCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAtADCCDF::~PieceAtADCCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAtADCCDF::entry(){
	PRINT_STATE;
	data->timeprofile.fast_timestamps[(int)Timestamp::ADC_BLOCKED] = data->stopwatch.peek_time();
}

void PieceAtADCCDF::exit(){
	PRINT_STATE;
}

State* PieceAtADCCDF::adc_top_area_unblocked(){
	return new ADCToGateCDF(data);
}