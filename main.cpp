#include <iostream>
#include "Dispatcher.h"
#include "Ithreadcom.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>

int main(){
	system("gns -s ");
	Dispatcher *dispatcher = new Dispatcher();
	std::thread disp(&Dispatcher::run_dispatcher, dispatcher);
	printf("Dispatcher started \n");

	_pulse event;
	int event_info;

	Ithread_com *threadcom_hal = new Ithread_com(FBM_1_HAL);
	printf("staring Hal\n");
	Ithread_com *threadcom_fsm = new Ithread_com(FBM_1_FSM);
	printf("staring Fsm\n");
	Ithread_com *threadcom_com = new Ithread_com(FBM_1_COM);
	printf("staring Com\n");
	Ithread_com *threadcom_rec = new Ithread_com(FBM_1_RECORDER);
	printf("staring Rec\n");
	Ithread_com *threadcom_rem = new Ithread_com(FBM_1_REMOTE);
	printf("staring Rem\n");

	event_info = threadcom_hal->receive_event(&event);
	if(event_info == 1){
		if(event.code == 12){
			printf("Dispatcher connected with Hal\n");
		}
	}
	event_info = threadcom_fsm->receive_event(&event);
	if(event_info == 1){
		if(event.code == 12){
			printf("Dispatcher connected with FSm\n");
		}
	}
	event_info = threadcom_rec->receive_event(&event);
	if(event_info == 1){
		if(event.code == 12){
			printf("Dispatcher connected with Recorder\n");
		}
	}
	event_info = threadcom_com->receive_event(&event);
	if(event_info == 1){
		if(event.code == 12){
			printf("Dispatcher connected with Com\n");
		}
	}
	event_info = threadcom_rem->receive_event(&event);
	if(event_info == 1){
		if(event.code == 12){
			printf("Dispatcher connected with Remote\n");
		}
	}

	threadcom_hal->send_event(0, 0);

	event_info = threadcom_rec->receive_event(&event);
	if(event_info == 0){
		printf("received event\n");
	}
	else{
		printf("smth went wrong\n");
	}
}
