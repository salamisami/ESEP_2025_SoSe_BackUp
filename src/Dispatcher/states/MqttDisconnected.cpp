/*
 * MqttDisconnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "MqttDisconnected.h"
#include <stdio.h>

void MqttDisconnected::dispatch_message(){ }

void MqttDisconnected::dispatcher_ready(){ }

void MqttDisconnected::entry(){
	printf("entering MqttDisconnectd\n");
	data->set_mqtt_connection(false);
	data->set_rcid_mqtt(0);
}

void MqttDisconnected::exit(){ }

void MqttDisconnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void MqttDisconnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void MqttDisconnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void MqttDisconnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void MqttDisconnected::mqtt_not_ready(){ }

void MqttDisconnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void MqttDisconnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void MqttDisconnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
