/*
 * EStop.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "EStop.h"

EStop::EStop(ContextData* data,State* substate) :
HState(data, substate, new Modehandler(data)){};

void EStop::entry(){ }

void EStop::exit(){
	data->sender->send_event( (int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF,(int)EventPriority::DEFAULT);
}

State* EStop::clone(){
	return new EStop(data, this->substate->clone());
}

State* EStop::error_c_lost_com(){
	State* cloned = this->clone();
	data->estop_history->push(cloned);
	return new ErrorCom(data);
}

State* EStop::error_c_lost_mqtt(){
	State* cloned = this->clone();
	data->estop_history->push(cloned);
	return new ErrorCom(data);
}
