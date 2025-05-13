/*
 * MqttConnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "MqttConnected.h"
#include <stdio.h>
#include <thread>

#define GNS_MQTT "MQTT"

void MqttConnected::dispatch_message(){ }

void MqttConnected::dispatcher_ready(){
	exit();
	new(this) DispatcherOnline;
	entry();
}

void MqttConnected::entry(){
	printf("entering MqttConnected\n");
	data->set_mqtt_connection(true);

	int rcid = action->build_connection(GNS_MQTT);
	if(rcid == -1){
		//FAILED CONNECTION
		return;
	}
	data->set_rcid_mqtt(rcid);

	if(action->all_connected()){
		exit();
		new(this) DispatcherOnline;
		entry();
	}
}

void MqttConnected::exit(){ }

void MqttConnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void MqttConnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void MqttConnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void MqttConnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void MqttConnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void MqttConnected::mqtt_ready(){ }

void MqttConnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void MqttConnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
