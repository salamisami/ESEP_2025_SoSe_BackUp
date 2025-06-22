#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
#include "COM.h"
#include "Timer.h"
#include "Logic.h"
#include "Event.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    system("gns -s ");

    Dispatcher* dispatcher = new Dispatcher();
    std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

    Thread_COM::Sender* com_dispatcher_sender = new Thread_COM::Sender(FBM_2_DISPATCHER);

    Thread_COM::Receiver* com_receiver = new Thread_COM::Receiver(FBM_2_COM); //empfängt andere Maschine
    Thread_COM::Receiver* com_dispatcher_receiver = new Thread_COM::Receiver(FBM_2_COM_RECEIVER); //empfängt lokalen dispatcher





    COM*  externCommunication = new COM(com_receiver, FBM_1_COM, com_dispatcher_receiver, com_dispatcher_sender);
    externCommunication->start();
    Thread_COM::Sender* senderDispatcher = new Thread_COM::Sender(FBM_2_DISPATCHER);
    int8_t comCode = (int8_t) Topic::COM;
    int value = (int) COM_Enum::BUTTON_ESTOP_PRESSED;
    while (true){
		senderDispatcher-> send_event(comCode, value);
		auto remaining = std::chrono::milliseconds(5000);
		COUT("sending Estop.");
		std::this_thread::sleep_for(remaining);
    }


    while(1){

    }
    
    cout << "Program Finished." << endl;
    return 0;
}
