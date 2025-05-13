/*
 * action.cpp
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#include "Action.h"
#include "DispatcherEvents.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

Action::Action(Data *data) {
	this->data = data;
}

int Action::build_connection(char* attach_point){
	int receiver_coid;
	receiver_coid = name_open(attach_point, NAME_FLAG_ATTACH_GLOBAL);
	if (-1 == receiver_coid){
		perror("sender: name_open failed");
		return -1;
	}
	return receiver_coid;
}

int Action::send_event(){
	MsgSendPulse(data->get_rcid_fsm(), SIGEV_PULSE_PRIO_INHERIT, data->get_event(), 0);
	MsgSendPulse(data->get_rcid_hal(), SIGEV_PULSE_PRIO_INHERIT, data->get_event(), 0);
	MsgSendPulse(data->get_rcid_mqtt(), SIGEV_PULSE_PRIO_INHERIT, data->get_event(), 0);
	MsgSendPulse(data->get_rcid_qnet(), SIGEV_PULSE_PRIO_INHERIT, data->get_event(), 0);
	return 0;
}

bool Action::all_connected(){
	if(data->fsm_connected() && data->hal_connected() && data->mqtt_connected() && data->qnet_connected()){
		return true;
	}
	return false;
}

int Action::dispatcher_online(){
		int receiver_coid;
		receiver_coid = name_open(GNS_NAME, NAME_FLAG_ATTACH_GLOBAL);
		if (-1 == receiver_coid){
			perror("sender: name_open failed");
			return -1;
		}

		MsgSendPulse(receiver_coid, SIGEV_PULSE_PRIO_INHERIT, DISPATCHER_ONLINE, 0);
		return 0;
}
