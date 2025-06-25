#include "Fast.h"

//================================================= constructors & destructors =================================================
Fast::Fast(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Fast::~Fast() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Fast::entry(){
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
	data->piece->fast();
	PRINT_STATE;
}

void Fast::exit(){
	PRINT_STATE;
}

State* Fast::button_reset_pressed(){
	return new Slow(data);
}