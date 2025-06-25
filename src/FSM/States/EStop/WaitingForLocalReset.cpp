/*
 * WaitingForLocalReset.cpp
 *
 *  Created on: 25.06.2025
 *      Author: User
 */
#include "WaitingForLocalReset.h"

WaitingForLocalReset::WaitingForLocalReset(ContextData* data) : State(data) {};

WaitingForLocalReset::~WaitingForLocalReset() {};

void WaitingForLocalReset::entry(){}

void WaitingForLocalReset::exit(){}

State* WaitingForLocalReset::button_estop_pressed(){
	return new EStopViaLocal(data);
}

State* WaitingForLocalReset::com_button_estop_pressed(){
	return new EStopViaNeighbor(data);
}

State* WaitingForLocalReset::estop(){
	return new EStopReleased(data);
}

State* WaitingForLocalReset::button_reset_pressed(){
	data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_OFF);
	return new IdleIM(data);
}


