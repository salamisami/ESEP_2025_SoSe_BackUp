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
#include "Fsm.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <csignal>
#include <atomic>

#ifndef NO_RC_REC
#include "inc/MQTT/MQTT_Utilities.h"
#endif

#define ONE_MILLISECOND 1000
#define COUT(msg) std::cout << msg << std::endl
using namespace std;


#define ONE_MILLISECOND 1000

using namespace std;

int main() {

    //std::thread inputThread(wait_for_enter);

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
    #ifndef NO_RC_REC
    Thread_COM::Receiver* recorder_receiver = new Thread_COM::Receiver(FBM_N_RECORDER); //comment this to test without recorder
    #endif
    Thread_COM::Sender* recorder_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);
    #ifndef NO_RC_REC
    Thread_COM::Receiver* RemCon_receiver = new Thread_COM::Receiver(FBM_N_REMOTE); //comment this to test without RC
    #endif
    Thread_COM::Sender* RemCon_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

    Thread_COM::Sender* com_sender_local = new Thread_COM::Sender(FBM_N_DISPATCHER);

    #ifndef NO_COM
    Thread_COM::Receiver* com_external_receiver = new Thread_COM::Receiver(FBM_N_COM);
    Thread_COM::Receiver* com_receiver_local = new Thread_COM::Receiver(FBM_N_COM_RECEIVER);
    #endif

    Thread_COM::Receiver* hal_receiver = new Thread_COM::Receiver(FBM_N_HAL);
    Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);


    auto logic = new Logic<Fsm>(fsm_receiver, fsm_sender);

    #ifndef NO_RC_REC
    Recorder* rec = new Recorder(recorder_receiver, recorder_sender);
    Remote_Controller* remcon = new Remote_Controller(RemCon_receiver, RemCon_sender); //comment this to test without RC
    #endif

    #ifndef NO_COM
    COM* externCommunication = new COM(com_external_receiver, FBM_N_COM_EXT, com_receiver_local, com_sender_local);
    externCommunication->start();
    #endif

    HAL* hal = new HAL(hal_receiver, hal_sender);

    #ifndef NO_RC_REC
    while(Remote_Controller::Main_running) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    #else
    while(1){}
    #endif

    delete hal;

    #ifndef NO_COM
    delete externCommunication;
    #endif

    #ifndef NO_RC_REC
    delete remcon;
    delete rec;
    #endif

    delete logic;

    delete hal_sender;
    delete hal_receiver;

    #ifndef NO_COM
    delete com_receiver_local;
    delete com_external_receiver;
    #endif

    delete com_sender_local;
    delete RemCon_sender;

    #ifndef NO_RC_REC
    delete RemCon_receiver;
    #endif

    delete recorder_sender;

    #ifndef NO_RC_REC
    delete recorder_receiver;    
    #endif

    delete fsm_sender;
    delete fsm_receiver;

    delete dispatcher;

    cout << "Program Finished." << endl;
    return 0;


}
