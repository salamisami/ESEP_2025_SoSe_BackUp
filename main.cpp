#include "Dispatcher.h"
#include "Thread_COM.h"

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
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

	//TODO Don't forget to free the memory, allocated using new. Because the objects here are initialized to heap, not stack.
	Thread_COM::Receiver *threadcom_hal = new Thread_COM::Receiver(FBM_1_HAL);
	printf("staring Hal\n");
	Thread_COM::Receiver *threadcom_fsm = new Thread_COM::Receiver(FBM_1_FSM);
	printf("staring Fsm\n");
	Thread_COM::Receiver *threadcom_com = new Thread_COM::Receiver(FBM_1_COM);
	printf("staring Com\n");
	Thread_COM::Receiver *threadcom_rec = new Thread_COM::Receiver(FBM_1_RECORDER);
	printf("staring Rec\n");
	Thread_COM::Receiver *threadcom_rem = new Thread_COM::Receiver(FBM_1_REMOTE);
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


	Thread_COM::Sender* send_test = new Thread_COM::Sender(FBM_1_HAL);
	send_test->send_event(0, 0);

	event_info = threadcom_rec->receive_event(&event);
	if(event_info == 0){
		printf("received event\n");
	}
	else{
		printf("smth went wrong\n");
	}
}
