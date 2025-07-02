#include "Green.h"

//================================================= constructors & destructors =================================================
Green::Green(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Green::~Green() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Green::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
}

void Green::exit(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Green::button_start_pressed(){
	return new Yellow(data);
}

State* Green::clone(){
	return new Green(data);
}