/*
 * ErrorCom.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include"ErrorCom.h"

void ErrorCom::entry(){}

void ErrorCom::exit() { }

State* ErrorCom::mqtt_error_resolved() {
	data->mqtt_resolved = true;
	if(data->mqtt_resolved && data->com_resolved){
		if(data->is_estop){
			State* estop = data->estop_history->top();
			data->estop_history->pop();
			return estop;
		}
		else{
			State* modehandler = data->modehandler_history->top();
			data->modehandler_history->pop();
			//TODO check for EstopPressed and send Event
			return modehandler;
		}
	}
	return nullptr;
	
	
}

State* ErrorCom::com_error_resolved() {
	data->com_resolved = true;
	if(data->mqtt_resolved && data->com_resolved){
		if(data->is_estop){
			State* estop = data->estop_history->top();
			data->estop_history->pop();
			return estop;
		}

		else{
			State* modehandler = data->modehandler_history->top();
			data->modehandler_history->pop();
			//TODO check for EstopPressed and send Event
			return modehandler;
		}
	}
	return nullptr;
}

State* ErrorCom::error_c_lost_mqtt(){
	data->mqtt_resolved = false;
	return nullptr;
}

State* ErrorCom::error_c_lost_com(){
	data->com_resolved = false;
	return nullptr;
}

State* ErrorCom::clone() {
	return new ErrorCom(data);
}
