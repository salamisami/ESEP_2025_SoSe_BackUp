#include "ADCToGateCDF.h"

//================================================= constructors & destructors =================================================
ADCToGateCDF::ADCToGateCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ADCToGateCDF::~ADCToGateCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCToGateCDF::entry(){
	PRINT_STATE;
	data->timeprofile.timestamp[(int)Timestamp::ADC_UNBLOCKED] = data->stopwatch.peek_time();

}

void ADCToGateCDF::exit(){
	PRINT_STATE;
}

State* ADCToGateCDF::laser_sorting_gate_blocked(){
	return new PieceAtGateCDF(data);
}