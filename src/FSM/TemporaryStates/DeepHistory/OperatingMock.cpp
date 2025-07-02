#include "OperatingMock.h"

//================================================= constructors & destructors =================================================
OperatingMock::OperatingMock(ContextData* data) : OrthState(
	data,
	{ new TrafficMock(data), new MotorDisable(data) },
	new IdleMock(data)
) {
}

OperatingMock::OperatingMock(ContextData* data, std::vector<State*> cloned_substates) : OrthState(data, cloned_substates, new IdleMock(data)) {}

OperatingMock::~OperatingMock() {
	//OrthState::~OrthState();
}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================

State* OperatingMock::clone() {
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
	data->modehandler_history->push(clone());
	return new IdleMock(data);
}