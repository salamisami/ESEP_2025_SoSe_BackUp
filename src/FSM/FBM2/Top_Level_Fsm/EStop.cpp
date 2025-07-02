/*
 * EStop.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include "EStop.h"

void EStop::entry(){ }

void EStop::exit(){
	data->sender->send_event(Topic.ACTUATOR, ActuatorEnum.TRAFFIC_RED_OFF);
}

State* EStop::clone(){
	return new EStop(data, this->substate->clone());
}

State* EStop::error_c_lost_com(){
	EStop* cloned = this->clone();
	data->estop_history->push(cloned);
	return new ErrorCom(data);
}

State* EStop::error_c_lost_mqtt(){
	EStop* cloned = this->clone();
	data->estop_history->push(cloned);
	return new ErrorCom(data);
}
