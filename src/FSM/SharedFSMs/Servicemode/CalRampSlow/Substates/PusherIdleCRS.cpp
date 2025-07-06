#include "PusherIdleCRS.h"

//================================================= constructors & destructors =================================================
PusherIdleCRS::PusherIdleCRS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PusherIdleCRS::~PusherIdleCRS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PusherIdleCRS::entry(){
	PRINT_STATE;
}

void PusherIdleCRS::exit(){
	PRINT_STATE;
}

State* PusherIdleCRS::adc_top_area_blocked(){
	return new SendToRamp(data);
}

State* PusherIdleCRS::clone() {
	return new PusherIdleCRS(data);
}