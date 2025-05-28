#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"

#include "Timer.h"
#include "Logic.h"

#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    Mock_PM::Receiver* logic_receiver = new Mock_PM::Receiver();
    Mock_PM::Sender* remote_control = new Mock_PM::Sender(logic_receiver);
    I_Sender* timer_sender = new Mock_PM::Sender(logic_receiver);



    //ContextData* data = new ContextData(remote_control, local_receiver, timer_sender);
    //Context<ModeHandler>* fsm = new Context<ModeHandler>(data);

    //Timer* timer = new Timer(timer_sender);

    //timer->setTimer(2000, 1);
    //timer->setTimer(2000, 2);

    // //TODO Problem: Beide Timer müssen gleichzeitig beenden
    // int eventNo = 0;
    // for(int i = 0; i < 2; i++) {
    //     _pulse event;
    //     local_receiver->receive_event(&event);
    //     eventNo++;
    //     printf("Event Number: %d\n", eventNo);
    // }
    // printf("End of State.\n");

    // delete timer;
    // // delete fsm;
    // // delete data;
    // delete timer_sender;

    remote_control->send_event((int8_t)Topic::STOP_THREAD,0);

    Logic logic = Logic(logic_receiver, remote_control, timer_sender);
    WAIT(1000);

    delete remote_control;
    delete logic_receiver;
    cout << "Program Finished." << endl;
    return 0;
}
