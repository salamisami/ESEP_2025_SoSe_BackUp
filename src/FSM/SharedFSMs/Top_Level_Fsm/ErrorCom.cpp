/*
 * ErrorCom.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include"ErrorCom.h"

void ErrorCom::entry() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
}

void ErrorCom::exit() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

State* ErrorCom::mqtt_error_resolved() {
	data->mqtt_resolved = true;
	if(!data->com_resolved || !data->mqtt_resolved) {
		return nullptr;
	}
	if(data->is_estop) {
		State* estop = data->estop_history->top();
		data->estop_history->pop();
		return estop;
	}
	State* modehandler = data->modehandler_history->top();
	return modehandler;
}

State* ErrorCom::com_error_resolved() {
	data->com_resolved = true;
	if(!data->com_resolved || !data->mqtt_resolved) {
		return nullptr;
	}
	if(data->is_estop) {
		State* estop = data->estop_history->top();
		data->estop_history->pop();
		return estop;
	}
	State* modehandler = data->modehandler_history->top();
	data->modehandler_history->pop();
	return modehandler;
}

State* ErrorCom::error_c_lost_com(){
	  data->com_resolved = false;
	  return nullptr;
}

State* ErrorCom::error_c_lost_mqtt(){
	  data->mqtt_resolved = false;
	  return nullptr;
}

State* ErrorCom::clone() {
	return new ErrorCom(data);
}

