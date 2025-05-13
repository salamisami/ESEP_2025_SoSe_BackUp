/*
 * HalDisconnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: Thomas
 */

#include "HalDisconnected.h"
#include <stdio.h>

void HalDisconnected::dispatch_message(){ }

void HalDisconnected::dispatcher_ready(){ }

void HalDisconnected::entry(){
	printf("entering HalDisconnected\n");
	data->set_hal_connection(false);
	data->set_rcid_hal(0);
}

void HalDisconnected::exit(){ }

void HalDisconnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void HalDisconnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void HalDisconnected::hal_not_ready(){ }

void HalDisconnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void HalDisconnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void HalDisconnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void HalDisconnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void HalDisconnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
