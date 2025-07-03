#include "IsMetal_PT1.h"

//================================================= constructors & destructors =================================================
IsMetal_PT1::IsMetal_PT1(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IsMetal_PT1::~IsMetal_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IsMetal_PT1::entry(){
	PRINT_STATE;
}

void IsMetal_PT1::exit(){
	PRINT_STATE;
}

State* IsMetal_PT1::clone(){
	return new IsMetal_PT1(data);
}