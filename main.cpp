#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
#include "Recorder.h"
#include "COM.h"
#include "Timer.h"
#include "Logic.h"
#include "Event.h"
#include "Remote_Controller.h"
#include "inc/MQTT/MQTT_Utilities.h"

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
 Thread_COM::Receiver* recorder_receiver = new Thread_COM::Receiver(FBM_N_RECORDER);
  Thread_COM::Sender* recorder_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

  Thread_COM::Receiver* RemCon_receiver = new Thread_COM::Receiver(FBM_N_REMOTE); //comment this to test without RC
  Thread_COM::Sender* rc_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

  Thread_COM::Sender* com_sender_local = new Thread_COM::Sender(FBM_N_DISPATCHER);
  Thread_COM::Receiver* com_external_receiver = new Thread_COM::Receiver(FBM_N_COM);
  Thread_COM::Receiver* com_receiver_local = new Thread_COM::Receiver(FBM_N_COM_RECEIVER);

  Thread_COM::Receiver* hal_receiver = new Thread_COM::Receiver(FBM_N_HAL);
  Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);
  

  // Timestamp slow: 6707
  // Timestamp slow: 7987
  // Timestamp slow: 11583
  // Timestamp slow: 13239
  // Timestamp slow: 19122
  // Timestamp slow: 11847
  // TimeProfile fast_profile = { {2165, 2560, 3651, 4150, 5908, 4050} };
  // TimeProfile slow_profile = { {6707, 7987, 11583, 13239, 19122, 11847} };

  // int tick_duration = 10;
  // Piece* piece = new Piece(slow_profile, fast_profile, tick_duration);
  // piece->slow();
  // while(true){
  //     std::cout << "Area: " << (int) piece->getArea() << ", " << "Position: " << (double) piece->getPosition() << std::endl;
  //     WAIT(500);
  // }


   
    
   
   

  Logic* logic = new Logic(fsm_receiver, fsm_sender);
  //start recorder here
  //Remote_Controller* remcon = new Remote_Controller(RemCon_receiver, rc_sender); //comment this to test without RC


    
    //start recorder here
    Recorder* rec = new Recorder(recorder_receiver,recorder_sender);

    Remote_Controller* remcon = new Remote_Controller(RemCon_receiver, rc_sender); //comment this to test without RC
  COM* externCommunication = new COM(com_external_receiver, FBM_N_COM_EXT, com_receiver_local, com_sender_local);
  externCommunication->start();

  // Thread_COM::Sender* senderDispatcher = new Thread_COM::Sender(FBM_N_DISPATCHER);
  // int8_t comCode = (int8_t) Topic::COM;
  // int value = (int) COM_Enum::BUTTON_ESTOP_PRESSED;

  HAL* hal = new HAL(hal_receiver, hal_sender);

  /*while (true){
  senderDispatcher-> send_event(comCode, value);
  auto remaining = std::chrono::milliseconds(5000);
  COUT("sending Estop.");
  std::this_thread::sleep_for(remaining);
  }*/
  // WAIT(3000);

  // delete def;
  // delete abc;

  // delete hal_sender;
  // delete fsm_sender;
  // delete fsm_receiver;
  // delete hal_receiver;

  while(1) {

  }
   delete hal;
   delete rec;
   delete logic;
   delete remcon;

   delete RemCon_receiver;
   delete rc_sender;
   delete recorder_receiver;
   delete recorder_sender;
   delete hal_sender;
   delete fsm_sender;
   delete fsm_receiver;
   delete hal_receiver;


  cout << "Program Finished." << endl;
  return 0;


}
