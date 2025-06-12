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
    I_Sender* to_self_sender = new Mock_PM::Sender(logic_receiver);



    Logic* logic = new Logic(logic_receiver, logic_sender, to_self_sender);
    WAIT(1000); 
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(3000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(5000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_PRESSED);
    remote_control->send_event((int8_t) Topic::STOP_THREAD, 0);
    WAIT(1000);

    delete logic;
    delete to_self_sender;
    delete logic_sender;
    delete hal_receiver;
    delete remote_control;
    delete logic_receiver;
    cout << "Program Finished." << endl;
    return 0;


}
