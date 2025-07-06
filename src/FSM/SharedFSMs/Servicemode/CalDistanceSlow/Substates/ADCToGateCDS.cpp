#include "ADCToGateCDS.h"

//================================================= constructors & destructors =================================================
ADCToGateCDS::ADCToGateCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ADCToGateCDS::~ADCToGateCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCToGateCDS::entry(){
	PRINT_STATE;
	data->timeprofile.slow_timestamps[(int)Timestamp::ADC_UNBLOCKED] = data->stopwatch.peek_time();

}

void ADCToGateCDS::exit(){
	PRINT_STATE;
}

State* ADCToGateCDS::laser_sorting_gate_blocked(){
	return new PieceAtGateCDS(data);
}

State* ADCToGateCDS::clone() {
	return new ADCToGateCDS(data);
}