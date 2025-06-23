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

OperatingMock::~OperatingMock() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OperatingMock::entry(){
	PRINT_STATE;
	OrthState::entry();
}

void OperatingMock::exit(){
	OrthState::exit();
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
}

//save history
State* OperatingMock::button_stop_pressed(){
	OrthState* cloned_state = OrthState::clone();
	data->stateStack->push(cloned_state);
	return new IdleIM(data);
}