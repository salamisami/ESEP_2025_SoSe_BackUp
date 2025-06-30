#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Idle::~Idle() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Idle::entry(){
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	PRINT_STATE;
}

void Idle::exit(){
    //TODO:Update data
    PRINT_STATE;
}

State* Idle::motor_fast(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
    return new Fast(data);
}