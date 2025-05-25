#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Event.h"
#include "ModeHandler.h"
#include "HAL.h"
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
#include <iostream>
#include "TrafficUtility.h"

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    system("gns -s ");
    
    Dispatcher* dispatcher = new Dispatcher();
    std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

    Thread_COM::Receiver* hal_receiver =  new Thread_COM::Receiver(FBM_1_HAL);
    Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);
    Thread_COM::Receiver* fsm_receiver = new Thread_COM::Receiver(FBM_1_FSM);
    Thread_COM::Sender* fsm_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);
    
    I_Sender* timer_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);

    Thread_COM::Sender* abc = new Thread_COM::Sender(FBM_1_DISPATCHER);
    Thread_COM::Sender* def = new Thread_COM::Sender(FBM_1_DISPATCHER);
    

    ContextData* data = new ContextData(fsm_sender, fsm_receiver, timer_sender);
    Context<ModeHandler>* fsm = new Context<ModeHandler>(data);

    HAL* hal = new HAL(hal_receiver, hal_sender);
    DEBUG("HAL is started");

    bool fsm_running = true;
    int eventNo = 0;
    while(fsm_running) {
        _pulse event;
        fsm_receiver->receive_event(&event);
        eventNo++;
        printf("Event Number: %d\n", eventNo);
        if((Topic) event.code == Topic::INTERRUPT && (InterruptEnum) event.value.sival_int == InterruptEnum::BUTTON_RESET_PRESSED){
            fsm_running = false;
        }
        fsm->handleEvent(event);
    }
    printf("End of State.\n");

    delete hal;
    delete fsm;
    delete data;
    delete timer_sender;

    delete hal_sender;
    delete fsm_sender;
    delete fsm_receiver;
    delete hal_receiver;

    cout << "Program Finished." << endl;
    return 0;
}
