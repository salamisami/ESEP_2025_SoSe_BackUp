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
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
}

void MotorEnable::exit(){
	PRINT_STATE;
}

State* MotorEnable::button_reset_pressed(){
	return new MotorDisable(data);
}

State* MotorEnable::clone(){
	return new MotorEnable(data);
}