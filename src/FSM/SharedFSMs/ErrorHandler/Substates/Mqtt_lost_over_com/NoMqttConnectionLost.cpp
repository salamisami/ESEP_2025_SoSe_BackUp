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

State* NoMqttConnectionLost::com_mqtt_disconnected(){
	return new MqttConnectionLostOverCom(data);
}
