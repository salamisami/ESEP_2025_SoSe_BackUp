#include "OperatingMock.h"

//================================================= constructors & destructors =================================================
OperatingMock::OperatingMock(ContextData* data) : OrthState(
	data,
	std::vector<State*>({
		new Green(data),
		new MotorDisable(data)
		})
) {
	//substate = new SubState(data);
}

OperatingMock::OperatingMock(ContextData* data, std::vector<State*> cloned_substates) : OrthState(data, cloned_substates){
	
}

OperatingMock::~OperatingMock() {
	//OrthState::~OrthState();
}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================

State* OperatingMock::clone(){
	auto cloned_substates = OrthState::clone_substates();
	OperatingMock* cloned_state = new OperatingMock(data, cloned_substates);
	return cloned_state;
}

void OperatingMock::entry() {
	PRINT_STATE;
	OrthState::entry();
}

void OperatingMock::exit() {
	OrthState::exit();
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
}

//save history
State* OperatingMock::button_stop_pressed() {
	data->stateStack->push(clone());
	return new IdleIM(data);
}