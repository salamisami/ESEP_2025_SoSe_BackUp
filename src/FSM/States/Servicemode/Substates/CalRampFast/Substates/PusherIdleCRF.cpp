#include "PusherIdleCRF.h"

//================================================= constructors & destructors =================================================
PusherIdleCRF::PusherIdleCRF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PusherIdleCRF::~PusherIdleCRF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PusherIdleCRF::entry(){
	PRINT_STATE;
}

void PusherIdleCRF::exit(){
	PRINT_STATE;
}

State* PusherIdleCRF::adc_top_area_blocked(){
	return new SendToRamp(data);
}