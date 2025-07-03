#include "MovingToEnd_PT1.h"

//================================================= constructors & destructors =================================================
MovingToEnd_PT1::MovingToEnd_PT1(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MovingToEnd_PT1::~MovingToEnd_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MovingToEnd_PT1::entry(){
	PRINT_STATE;
}

void MovingToEnd_PT1::exit(){
	PRINT_STATE;
}

State* MovingToEnd_PT1::clone(){
	return new MovingToEnd_PT1(data);
}