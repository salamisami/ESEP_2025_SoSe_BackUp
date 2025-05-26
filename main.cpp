#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Event.h"
#include "ModeHandler.h"
#include "HAL.h"

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

    PulseMsg::Receiver* hal_receiver =  new PulseMsg::Receiver();
    PulseMsg::Receiver* fsm_receiver = new PulseMsg::Receiver();

    PulseMsg::Sender* fsm_sender = new PulseMsg::Sender(hal_receiver->getchid());
    PulseMsg::Sender* hal_sender = new PulseMsg::Sender(fsm_receiver->getchid());

    
    I_Sender* timer_sender = new PulseMsg::Sender(fsm_receiver->getchid());
    ContextData* data = new ContextData(fsm_sender, fsm_receiver, timer_sender);
    Context<ModeHandler>* fsm = new Context<ModeHandler>(data);

    HAL* hal = new HAL(hal_receiver, hal_sender);

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
