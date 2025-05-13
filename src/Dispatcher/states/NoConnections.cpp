/*
 * NoConnections.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "NoConnections.h"
#include <stdio.h>

void NoConnections::entry(){
	printf("entering NoConnections\n");
}

void NoConnections::exit(){ }

void NoConnections::fsm_not_ready(){ }

void NoConnections::hal_not_ready(){ }

void NoConnections::dispatch_message(){ }

void NoConnections::mqtt_not_ready(){ }

void NoConnections::qnet_not_ready(){ }

void NoConnections::dispatcher_ready(){ }

void NoConnections::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void NoConnections::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void NoConnections::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void NoConnections::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}

