/*
 * NoMqttConnectionLost.cpp
 *
 *  Created on: 06.07.2025
 *      Author: User
 */

#include "NoMqttConnectionLost.h"



NoMqttConnectionLost::NoMqttConnectionLost(ContextData* data) : State(data) {}

NoMqttConnectionLost::~NoMqttConnectionLost(){}

void NoMqttConnectionLost::entry(){}

void NoMqttConnectionLost::exit() {}

State* NoMqttConnectionLost::error_c_lost_mqtt(){
	return new MqttConnectionLostOverCom(data);
}
