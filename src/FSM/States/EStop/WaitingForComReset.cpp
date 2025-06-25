/*
 * WaitingForComReset.cpp
 *
 *  Created on: 25.06.2025
 *      Author: User
 */
#include "WaitingForComReset.h"

WaitingForComReset::WaitingForComReset(ContextData* data) : State(data) {};

WaitingForComReset::~WaitingForComReset() {};

void WaitingForComReset::entry(){}

void WaitingForComReset::exit(){}

State* WaitingForComReset::button_estop_pressed(){
	return new EStopViaLocal(data);
}

State* WaitingForComReset::com_button_estop_pressed(){
	return new EStopViaNeighbor(data);
}

State* WaitingForComReset::estop(){
	return new EStopReleased(data);
}

State* WaitingForComReset::com_button_reset_pressed(){
	data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_OFF);
	return new IdleIM(data);
}

