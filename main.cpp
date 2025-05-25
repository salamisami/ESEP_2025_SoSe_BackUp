#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"

#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    Mock_PM::Receiver* local_receiver = new Mock_PM::Receiver();
    Mock_PM::Sender* remote_control = new Mock_PM::Sender(local_receiver);
    I_Sender* timer_sender = new Mock_PM::Sender(local_receiver);

    ContextData* data = new ContextData(remote_control, local_receiver, timer_sender);
    Context<ModeHandler>* fsm = new Context<ModeHandler>(data);

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);

    int eventNo = 0;
    for(int i = 0; i < 2; i++) {
        _pulse event;
        local_receiver->receive_event(&event);
        eventNo++;
        printf("Event Number: %d\n", eventNo);
        fsm->handleEvent(event);
    }
    printf("End of State.\n");

    delete fsm;
    delete data;
    delete timer_sender;
    delete remote_control;
    delete local_receiver;
    cout << "Program Finished." << endl;
    return 0;
}
