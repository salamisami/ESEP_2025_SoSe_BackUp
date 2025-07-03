#include "SortingOut_PT1.h"

//================================================= constructors & destructors =================================================
SortingOut_PT1::SortingOut_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

SortingOut_PT1::~SortingOut_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SortingOut_PT1::entry(){
	PRINT_STATE;
}

void SortingOut_PT1::exit(){
	PRINT_STATE;
}

State* SortingOut_PT1::clone(){
	return new SortingOut_PT1(data, localdata_);
}