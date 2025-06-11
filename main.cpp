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

    Mock_PM::Receiver* hal_receiver = new Mock_PM::Receiver();
    Mock_PM::Sender* logic_sender = new Mock_PM::Sender(hal_receiver);
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


    Logic* logic = new Logic(logic_receiver, logic_sender, timer_sender);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_PRESSED);
    remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::BUTTON_ESTOP_PRESSED);
    remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::BUTTON_ESTOP_RELEASED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_RELEASED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_RELEASED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::STOP_THREAD, 0);
    WAIT(1000);

    delete logic;
    delete timer_sender;
    delete logic_sender;
    delete hal_receiver;
    delete remote_control;
    delete logic_receiver;
    cout << "Program Finished." << endl;
    return 0;


}
