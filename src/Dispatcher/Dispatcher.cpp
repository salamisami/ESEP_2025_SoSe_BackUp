/*
 * Dispatcher.cpp
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#include "Dispatcher.h"
#include <iostream>





Dispatcher::Dispatcher() {
	switch(FBM){
	case 1:
		threadcom = new Thread_COM::Receiver(FBM_1_DISPATCHER);
		break;
	case 2:
		threadcom = new Thread_COM::Receiver(FBM_2_DISPATCHER);
		break;
	default:
		perror("Foerderbandmodul not defined");
		exit(-1);
	}
}

Dispatcher::~Dispatcher() {

}

void Dispatcher::run_dispatcher() {

//waiting for all components to connect to DispatcherS
	_pulse event;
	int event_info;
	int num_comp = 0;
	do{
		event_info = threadcom->receive_event(&event);
		if(event_info == -1){
			continue;
		}
		if(event_info == 0){
			continue;
		}
		if(event_info == 1){
            std::cout << "Received Eventinfo 1"
                      << std::endl;
			if(event.code == 12){
				num_comp++;
			}
		}
	}while(num_comp < MAX_NUM_COMP);
	 std::cout << "exiting while num_comp<max_nom_comp loop"<< std::endl;

//connecting to all Components
	switch(FBM){
	case 1:
		coid_arr[0] = name_open(FBM_1_HAL, NAME_FLAG_ATTACH_GLOBAL);
		coid_arr[1] = name_open(FBM_1_FSM, NAME_FLAG_ATTACH_GLOBAL);
		coid_arr[2] = name_open(FBM_1_RECORDER, NAME_FLAG_ATTACH_GLOBAL);
		coid_arr[3] = name_open(FBM_1_COM, NAME_FLAG_ATTACH_GLOBAL);
		coid_arr[4] = name_open(FBM_1_REMOTE, NAME_FLAG_ATTACH_GLOBAL);
		break;
	case 2: // wir sind FBM 2 1 Komponente zum weiterleiten: COM
		coid_arr[0] = name_open(FBM_2_COM_RECEIVER, NAME_FLAG_ATTACH_GLOBAL);
		break;
	default:
		perror("Foerderbandmodul not defined");
		exit(-1);
	}
	 std::cout << "name open for all FBM2 com done"<< std::endl;
	    // Print the single element
	 std::cout << "coid_arr[0] = " << coid_arr[0] <<std::endl;
//dispatching Messages
	while (1) {
		event_info = threadcom->receive_event(&event);
		if (event_info == -1) { // Error occurred
			perror("Dispatcher: threadcom->recieve_event() failed");
			continue;
		}
		if (event_info == 1) {
			continue;
		}
		if(event_info == 0){
            std::cout << "Received Event - Code: " << (int)event.code
                      << ", Value: " << event.value.sival_int
                      << std::endl;
			for(int i = 0;i < MAX_NUM_COMP;i++){
				switch(event.value.sival_int){
				default:
					MsgSendPulse(coid_arr[i],SIGEV_PULSE_PRIO_INHERIT,event.code,event.value.sival_int);
					break;
				}

			}
		}
	}
}

