#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
#include "COM.h"
#include "Timer.h"
#include "Logic.h"

#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    system("gns -c ");

    Dispatcher* dispatcher = new Dispatcher();
    std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

    Thread_COM::Receiver* com_receiver = new Thread_COM::Receiver(FBM_2_COM);
    Thread_COM::Receiver* com_dispatcher_receiver = new Thread_COM::Receiver(FBM_1_COM_RECEIVER);

    Thread_COM::Sender* com_dispatcher_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);



    COM*  externCommunication = new COM(com_receiver, FBM_1_COM, com_dispatcher_receiver, com_dispatcher_sender);
    externCommunication->start();



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
