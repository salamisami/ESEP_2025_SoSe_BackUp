#include "Red.h"

//================================================= constructors & destructors =================================================
Red::Red(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Red::~Red() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Red::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON);
}

void Red::exit(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
}

State* Red::button_start_pressed(){
	return new Green(data);
}

State* Red::clone(){
	return new Red(data);
}