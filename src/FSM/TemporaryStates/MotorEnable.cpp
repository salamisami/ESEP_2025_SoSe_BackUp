#include "MotorEnable.h"

//================================================= constructors & destructors =================================================
MotorEnable::MotorEnable(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MotorEnable::~MotorEnable() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MotorEnable::entry(){
	PRINT_STATE;
}

void MotorEnable::exit(){
	PRINT_STATE;
}

State* MotorEnable::button_reset_pressed(){
	return new MotorDisable(data);
}