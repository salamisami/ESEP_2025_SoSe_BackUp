#include "PieceMissing_PT1.h"

//================================================= constructors & destructors =================================================
PieceMissing_PT1::PieceMissing_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

PieceMissing_PT1::~PieceMissing_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceMissing_PT1::entry(){
	PRINT_STATE;
}

void PieceMissing_PT1::exit(){
	PRINT_STATE;
}

State* PieceMissing_PT1::clone(){
	return new PieceMissing_PT1(data, localdata_);
}