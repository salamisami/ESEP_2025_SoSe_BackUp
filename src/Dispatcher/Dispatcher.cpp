/*
 * Dispatcher.cpp
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#include "Dispatcher.h"






Dispatcher::Dispatcher() {
	threadcom = new Thread_COM::Receiver(FBM_N_DISPATCHER);
}

Dispatcher::~Dispatcher() {

}

void Dispatcher::run_dispatcher() {

	//waiting for all components to connect to DispatcherS
	_pulse event;
	int event_info;
	int num_comp = 0;
	do {
		event_info = threadcom->receive_event(&event);
		if(event_info == -1) {
			continue;
		}
		if(event_info == 0) {
			continue;
		}
		if(event_info == 1) {
			if(event.code == 12) {
				num_comp++;
			}
		}
	} while(num_comp < MAX_NUM_COMP);

	//connecting to all Components
	// coid_arr[0] = name_open(FBM_N_HAL, NAME_FLAG_ATTACH_GLOBAL);
	 coid_arr[1] = name_open(FBM_N_FSM, NAME_FLAG_ATTACH_GLOBAL);
	// coid_arr[2] = name_open(FBM_N_RECORDER, NAME_FLAG_ATTACH_GLOBAL);
	 coid_arr[0] = name_open(FBM_N_COM_RECEIVER, NAME_FLAG_ATTACH_GLOBAL);
	// coid_arr[4] = name_open(FBM_N_REMOTE, NAME_FLAG_ATTACH_GLOBAL);

	//dispatching Messages
	while(1) {
		event_info = threadcom->receive_event(&event);
		if(event_info == -1) { // Error occurred
			perror("Dispatcher: threadcom->recieve_event() failed");
			continue;
		}
		if(event_info == 1) {
			continue;
		}
		if(event_info == 0) {
			for(int i = 0; i < MAX_NUM_COMP; i++) {
				switch(event.value.sival_int) {
					default:
						MsgSendPulse(coid_arr[i], SIGEV_PULSE_PRIO_INHERIT, event.code, event.value.sival_int);
						break;
				}

			}
		}
	}
}

