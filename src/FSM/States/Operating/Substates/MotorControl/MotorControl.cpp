#include "MotorControl.h"


//================================================= constructors & destructors =================================================
MotorControl::MotorControl(ContextData* data) : OrthState(data,
	std::vector<State*>({
		new Idle(data)
		})
) {
	//substate = new SubState(data);
}

MotorControl::~MotorControl() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MotorControl::entry() {
	PRINT_STATE;
	
	OrthState::entry();
}

void MotorControl::exit() {
	OrthState::exit();
	PRINT_STATE;
}
