#include "EStopReleased.h"

//================================================= constructors & destructors =================================================
EStopReleased::EStopReleased(ContextData* data) : State(data) {}

EStopReleased::~EStopReleased() {}

//===================================================== private functions =====================================================

//void EStopReleased::privateFunction(){}

//===================================================== public functions =====================================================

void EStopReleased::entry(){
    PRINT_STATE;
	data->sender->send_event(Topic::ACTUATOR, ActuatorEnum::TRAFFIC_RED_ON);
	data->sender->send_event(Topic::ACTUATOR, ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

void EStopReleased::exit(){
	data->sender->send_event(Topic::ACTUATOR, ActuatorEnum::TRAFFIC_RED_OFF);
    PRINT_STATE;
}

State* EStopReleased::clone(){
	return new EStopReleased(data);
}

State* EStopReleased::com_button_reset_pressed(){
    return new WaitingForLocalReset(data);
}


State* EStopReleased::button_reset_pressed(){
    return new WaitingForComReset(data);
}

State* EStopReleased::button_estop_pressed(){
    return new EStopViaLocal(data);
}

State* EStopReleased::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}
