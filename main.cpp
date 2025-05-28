#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Event.h"
#include "ModeHandler.h"
#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"

#include "Timer.h"
#include "Logic.h"

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    system("gns -s ");

    Dispatcher* dispatcher = new Dispatcher();
    std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

    Thread_COM::Receiver* hal_receiver = new Thread_COM::Receiver(FBM_1_HAL);
    Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);
    Thread_COM::Receiver* fsm_receiver = new Thread_COM::Receiver(FBM_1_FSM);
    Thread_COM::Sender* fsm_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);

    Thread_COM::Sender* abc = new Thread_COM::Sender(FBM_1_DISPATCHER);
    Thread_COM::Sender* def = new Thread_COM::Sender(FBM_1_DISPATCHER);


    HAL* hal = new HAL(hal_receiver, hal_sender);
    Logic* logic = new Logic(fsm_receiver, fsm_sender);

    // WAIT(3000);

    // delete def;
    // delete abc;

    // delete hal_sender;
    // delete fsm_sender;
    // delete fsm_receiver;
    // delete hal_receiver;

    while(1){

    }
    
    cout << "Program Finished." << endl;
    return 0;
}
