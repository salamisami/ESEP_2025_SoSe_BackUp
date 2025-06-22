#include "Slow.h"

//================================================= constructors & destructors =================================================
Slow::Slow(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Slow::~Slow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Slow::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->piece->slow();

}

void Slow::exit(){
	PRINT_STATE;
}

State* Slow::button_reset_released(){
	return new Fast(data);
}