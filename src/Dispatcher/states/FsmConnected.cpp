/*
 * FsmConnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "FsmConnected.h"
#include <stdio.h>
#include <thread>

#define GNS_FSM "FSM"

void FsmConnected::dispatch_message(){ }

void FsmConnected::dispatcher_ready(){
	exit();
	new(this) DispatcherOnline;
	entry();
}

void FsmConnected::entry(){
	printf("entering FsmConnected\n");
	data->set_fsm_connection(true);
	int rcid = action->build_connection(GNS_FSM);
	if(rcid == -1){
		//FAILED CONNECTION
		return;
	}
	data->set_rcid_fsm(rcid);
	if(action->all_connected()){
		exit();
		new(this) DispatcherOnline;
		entry();
	}
}

void FsmConnected::exit(){ }

void FsmConnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void FsmConnected::fsm_ready(){ }

void FsmConnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void FsmConnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void FsmConnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void FsmConnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void FsmConnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void FsmConnected::qnet_ready(){
	exit();
	new(this) QnetConnected;
	entry();
}
