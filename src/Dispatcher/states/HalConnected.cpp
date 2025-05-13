/*
 * HalConnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "HalConnected.h"
#include <stdio.h>
#include <thread>

#define GNS_HAL "HAL"

void HalConnected::dispatch_message(){ }

void HalConnected::dispatcher_ready(){
	exit();
	new(this) DispatcherOnline;
	entry();
}

void HalConnected::entry(){
	printf("entering HalConnected\n");
	data->set_hal_connection(true);
	int rcid = action->build_connection(GNS_HAL);
	if(rcid == -1){
		//FAILED CONNECTION
		return;
	}
	data->set_rcid_hal(rcid);
	if(action->all_connected()){
		exit();
		new(this) DispatcherOnline;
		entry();
	}
}

void HalConnected::exit(){ }

void HalConnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void HalConnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void HalConnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void HalConnected::hal_ready(){ }

void HalConnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void HalConnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void HalConnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void HalConnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
