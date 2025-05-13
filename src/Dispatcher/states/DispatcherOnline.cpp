/*
 * DispatcherOnline.cpp
 *
 *  Created on: 09.05.2025
 *      Author: User
 */

#include "DispatcherOnline.h"
#include "Action.h"
#include <stdio.h>

void DispatcherOnline::dispatch_message(){
	action->send_event();
}

void DispatcherOnline::dispatcher_ready(){ }

void DispatcherOnline::entry(){
	printf("entering DispatcherOnline\n");
}

void DispatcherOnline::exit(){ }

void DispatcherOnline::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void DispatcherOnline::fsm_ready(){ }

void DispatcherOnline::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void DispatcherOnline::hal_ready(){ }

void DispatcherOnline::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void DispatcherOnline::mqtt_ready(){ }

void DispatcherOnline::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void DispatcherOnline::qnet_ready(){ }

