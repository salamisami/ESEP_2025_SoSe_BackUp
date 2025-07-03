#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
#include "Recorder.h"
#include "COM.h"
#include "Timer.h"
#include "Logic.h"
#include "Event.h"
#include "Remote_Controller.h"
#include "Boot.h"
#include "EStopTest.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

#include "inc/MQTT/MQTT_Utilities.h"
#define ONE_MILLISECOND 1000
#define COUT(msg) std::cout << msg << std::endl
using namespace std;


int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    system("slay gns");
    #ifdef FBM_1
    system("gns -s ");
    #else
    system("gns -c");
    #endif

    Dispatcher* dispatcher = new Dispatcher();
    std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

    Thread_COM::Receiver* fsm_receiver = new Thread_COM::Receiver(FBM_N_FSM);
    Thread_COM::Sender* fsm_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);
    Thread_COM::Receiver* recorder_receiver = new Thread_COM::Receiver(FBM_N_RECORDER); //comment this to test without recorder
    Thread_COM::Sender* recorder_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

    Thread_COM::Receiver* RemCon_receiver = new Thread_COM::Receiver(FBM_N_REMOTE); //comment this to test without RC
    Thread_COM::Sender* RemCon_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

    Thread_COM::Sender* com_sender_local = new Thread_COM::Sender(FBM_N_DISPATCHER);
    Thread_COM::Receiver* com_external_receiver = new Thread_COM::Receiver(FBM_N_COM);
    Thread_COM::Receiver* com_receiver_local = new Thread_COM::Receiver(FBM_N_COM_RECEIVER);

    Thread_COM::Receiver* hal_receiver = new Thread_COM::Receiver(FBM_N_HAL);
    Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);


    auto logic = new Logic<Boot>(fsm_receiver, fsm_sender);
    Recorder* rec = new Recorder(recorder_receiver, recorder_sender);
    Remote_Controller* remcon = new Remote_Controller(RemCon_receiver, RemCon_sender); //comment this to test without RC
    COM* externCommunication = new COM(com_external_receiver, FBM_N_COM_EXT, com_receiver_local, com_sender_local);
    externCommunication->start();
    HAL* hal = new HAL(hal_receiver, hal_sender);


    std::cin.get();  // Warten auf Enter

    delete hal;
    delete rec;
    delete logic;
    delete remcon;

     delete RemCon_receiver;
     delete RemCon_sender;
     delete recorder_receiver;
     delete recorder_sender;
     delete hal_sender;
     delete fsm_sender;
     delete fsm_receiver;
     delete hal_receiver;


  cout << "Program Finished." << endl;
  return 0;


}
