#include "GateEnd_PT1.h"

//================================================= constructors & destructors =================================================
GateEnd_PT1::GateEnd_PT1(ContextData* data, LocalDataPT1 localdata : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

GateEnd_PT1::~GateEnd_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void GateEnd_PT1::entry(){
	PRINT_STATE;
}

void GateEnd_PT1::exit(){
	PRINT_STATE;
}

State* GateEnd_PT1::clone(){
	return new GateEnd_PT1(data, localdata_);
}