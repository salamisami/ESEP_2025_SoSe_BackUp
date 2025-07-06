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
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
}

void MotorDisable::exit(){
	PRINT_STATE;
}

State* MotorDisable::button_reset_pressed(){
	return new MotorEnable(data);
}

State* MotorDisable::clone(){
	return new MotorDisable(data);
}

State* MotorDisable::laser_back_blocked() {
	return State::EXIT_STATE;
}