/*
 * FsmDisconnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "FsmDisconnected.h"
#include <stdio.h>

void FsmDisconnected::dispatch_message(){ }

void FsmDisconnected::dispatcher_ready(){ }

void FsmDisconnected::entry(){
	printf("entering FsmDisconnected\n");
	data->set_fsm_connection(false);
	data->set_rcid_fsm(0);
}

void FsmDisconnected::exit(){ }

void FsmDisconnected::fsm_not_ready(){ }

void FsmDisconnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void FsmDisconnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void FsmDisconnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void FsmDisconnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void FsmDisconnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void FsmDisconnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void FsmDisconnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
