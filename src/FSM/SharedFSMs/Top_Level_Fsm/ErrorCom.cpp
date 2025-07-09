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
  if (!data->com_resolved || !data->mqtt_resolved){
    return nullptr;
	if(data->is_estop){
		State* estop = data->estop_history->top();
		data->estop_history->pop();
		return estop;
	}
	State* modehandler = data->modehandler_history->top();
	return modehandler;
}

State* ErrorCom::com_error_resolved() {
  data->com_resolved = true;
  if (!data->com_resolved || !data->mqtt_resolved){
    return nullptr;
  }
	if(data->is_estop){
		State* estop = data->estop_history->top();
		data->estop_history->pop();
		return estop;
	}
	State* modehandler = data->modehandler_history->top();
	return modehandler;
}

State* ErrorCom::clone() {
	return new ErrorCom(data);
}
