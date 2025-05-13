/*
 * QnetDisconnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "QnetDisconnected.h"
#include <stdio.h>

void QnetDisconnected::dispatch_message(){ }

void QnetDisconnected::dispatcher_ready(){ }

void QnetDisconnected::entry(){
	printf("entering QnetDisconnected\n");
	data->set_qnet_connection(false);
	data->set_rcid_qnet(0);
}

void QnetDisconnected::exit(){ }

void QnetDisconnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void QnetDisconnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void QnetDisconnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void QnetDisconnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void QnetDisconnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void QnetDisconnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void QnetDisconnected::qnet_not_ready(){ }

void QnetDisconnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
