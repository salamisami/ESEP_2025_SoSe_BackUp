#include "Yellow.h"

//================================================= constructors & destructors =================================================
Yellow::Yellow(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Yellow::~Yellow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Yellow::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
}

void Yellow::exit(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

State* Yellow::button_start_pressed(){
	return new Red(data);
}

State* Yellow::clone(){
	return new Yellow(data);
}