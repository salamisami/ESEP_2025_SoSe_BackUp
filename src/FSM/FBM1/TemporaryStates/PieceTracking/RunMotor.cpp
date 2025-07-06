#include "RunMotor.h"

//================================================= constructors & destructors =================================================
RunMotor::RunMotor(ContextData* data) : State(data) {
	//substate = new SubState(data);
}

RunMotor::~RunMotor() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void RunMotor::entry() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	
}

void RunMotor::exit() {
	PRINT_STATE;
}

State* RunMotor::laser_front_unblocked() {
	return new SimulatePiece(data);
}