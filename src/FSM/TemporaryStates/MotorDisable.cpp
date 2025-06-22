#include "MotorDisable.h"

//================================================= constructors & destructors =================================================
MotorDisable::MotorDisable(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MotorDisable::~MotorDisable() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MotorDisable::entry(){
	PRINT_STATE;
}

void MotorDisable::exit(){
	PRINT_STATE;
}

State* MotorDisable::button_reset_pressed(){
	return new MotorEnable(data);
}