/*
 * QnetConnected.cpp
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#include "QnetConnected.h"
#include <stdio.h>
#include <thread>

#define GNS_QNET "QNET"

void QnetConnected::dispatch_message(){ }

void QnetConnected::dispatcher_ready(){
	exit();
	new(this) DispatcherOnline;
	entry();
}

void QnetConnected::entry(){
	printf("entering QnetConnected\n");
	data->set_qnet_connection(true);

	int rcid = action->build_connection(GNS_QNET);
	if(rcid == -1){
		//FAILED CONNECTION
		return;
	}
	data->set_rcid_qnet(rcid);
	if(action->all_connected()){
		exit();
		new(this) DispatcherOnline;
		entry();
	}
}

void QnetConnected::exit(){ }

void QnetConnected::fsm_not_ready(){
	exit();
	new(this) FsmDisconnected;
	entry();
}

void QnetConnected::fsm_ready(){
	exit();
	new(this) FsmConnected;
	entry();
}

void QnetConnected::hal_not_ready(){
	exit();
	new(this) HalDisconnected;
	entry();
}

void QnetConnected::hal_ready(){
	exit();
	new(this) HalConnected;
	entry();
}

void QnetConnected::mqtt_not_ready(){
	exit();
	new(this) MqttDisconnected;
	entry();
}

void QnetConnected::mqtt_ready(){
	exit();
	new(this) MqttConnected;
	entry();
}

void QnetConnected::qnet_not_ready(){
	exit();
	new(this) QnetDisconnected;
	entry();
}

void QnetConnected::qnet_ready(){ }
