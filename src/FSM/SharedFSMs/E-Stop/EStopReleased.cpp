#include "EStopReleased.h"

//================================================= constructors & destructors =================================================
EStopReleased::EStopReleased(ContextData* data) : State(data) {}

EStopReleased::~EStopReleased() {}

//===================================================== private functions =====================================================

//void EStopReleased::privateFunction(){}

//===================================================== public functions =====================================================

void EStopReleased::entry(){
    data->sender->send_event((int8_t) Topic::Actuator, (int) ActuatorEnum::LED_RESET_ON);
    PRINT_STATE;
	data->sender->send_event((int8_t)Topic::ACTUATOR,(int8_t) ActuatorEnum::TRAFFIC_RED_ON, (int8_t)EventPriority::DEFAULT);
}

void EStopReleased::exit(){
    data->sender->send_event((int8_t) Topic::Actuator, (int) ActuatorEnum::LED_RESET_OFF);
	data->sender->send_event((int8_t)Topic::ACTUATOR,(int8_t) ActuatorEnum::TRAFFIC_RED_OFF,(int8_t)EventPriority::DEFAULT);
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
