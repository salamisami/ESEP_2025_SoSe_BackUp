#include "Gate_PT1.h"

//================================================= constructors & destructors =================================================
Gate_PT1::Gate_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

Gate_PT1::~Gate_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Gate_PT1::entry(){
	PRINT_STATE;
}

void Gate_PT1::exit(){
	PRINT_STATE;
}

State* Gate_PT1::clone(){
	return new Gate_PT1(data, localdata_);
}

State* Gate_PT1::sort_out() {
	return new SortingOut_PT1(data, localdata_);
}
State* Gate_PT1::let_through() {
	return new GateEnd_PT1(data, localdata_);
}
State* Gate_PT1::sort_out_fbm2() {
	return new GateEnd_PT1(data. localdata_);
}