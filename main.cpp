#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"

#include "Timer.h"

#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    Mock_PM::Receiver* local_receiver = new Mock_PM::Receiver();
    Mock_PM::Sender* remote_control = new Mock_PM::Sender(local_receiver);
    I_Sender* timer_sender = new Mock_PM::Sender(local_receiver);

    //ContextData* data = new ContextData(remote_control, local_receiver, timer_sender);
    //Context<ModeHandler>* fsm = new Context<ModeHandler>(data);

    Timer* timer = new Timer(timer_sender);

    timer->setTimer(2000, 1);
    timer->setTimer(2000, 2);

    //TODO Problem: Beide Timer müssen gleichzeitig beenden
    int eventNo = 0;
    for(int i = 0; i < 2; i++) {
        _pulse event;
        local_receiver->receive_event(&event);
        eventNo++;
        printf("Event Number: %d\n", eventNo);
    }
    printf("End of State.\n");

    delete timer;
    // delete fsm;
    // delete data;
    delete timer_sender;
    delete remote_control;
    delete local_receiver;
    cout << "Program Finished." << endl;
    return 0;
}
