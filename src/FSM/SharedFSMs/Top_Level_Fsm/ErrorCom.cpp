/*
 * ErrorCom.cpp
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#include"ErrorCom.h"

void ErrorCom::entry(){}

void ErrorCom::exit() { }

State* ErrorCom::error_c_lost_mqtt_fixed() {
	if(data->is_estop){
		State* estop = data->estop_history->top();
		data->estop_history->pop();
		return estop;
	}
	State* modehandler = data->modehandler_history->top();
	return modehandler;
}

State* ErrorCom::error_c_lost_com_fixed() {
	if(data->is_estop){
		State* estop = data->estop_history->top();
		data->estop_history->pop();
		return estop;
	}
	State* modehandler = data->modehandler_history->top();
	return modehandler;
}

