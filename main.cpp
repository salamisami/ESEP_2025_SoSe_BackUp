#include "Context.h"
#include "Idle.h"
#include "Thread_COM.h"

#include <iostream>
int main() {

    // std::queue<Event> events;
    // events.push(Event::RESET);
    // events.push(Event::START);
    // events.push(Event::TICK);
    // events.push(Event::FORWARD);
    // events.push(Event::FORWARD);
    // events.push(Event::ESTOP);
    // events.push(Event::START);
    // events.push(Event::STOP);
    // events.push(Event::START);
    // events.push((Event::SERVICE));
    // events.push(Event::FORWARD);
    // events.push((Event::SERVICE));
    // events.push((Event::SERVICE));
    // events.push(Event::RESET);


    Context<Idle> fsm;
    int eventNo = 0;
    Thread_COM::Receiver receiver = Thread_COM::Receiver("FSM");
    while(!events.empty()) {
        _pulse event;
        receiver.receive_event(&event);
        eventNo++;
        printf("Event Number: %d\n", eventNo);
        fsm.handleEvent(event);
    }
    printf("End of State.\n");
    //delete fsm;
    /**
     * 1. QNet, wegen HAL
     * 2. Inner Events, Outside Events, Message Types
     *
     */

    return 0;
}