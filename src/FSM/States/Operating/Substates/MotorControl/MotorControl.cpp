#include "MotorControl.h"


//================================================= constructors & destructors =================================================
MotorControl::MotorControl(ContextData* data) : HState(data, new Idle(data)){}
MotorControl::MotorControl(ContextData* data, State* initial_state) : HState(data, initial_state) {}

MotorControl::~MotorControl() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MotorControl::entry() {
	PRINT_STATE;
	
	HState::entry();
}

void MotorControl::exit() {
	HState::exit();
	PRINT_STATE;
}

State* MotorControl::clone(){
  return new MotorControl(data, substate->clone());
}
