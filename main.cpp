#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
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


#define ONE_MILLISECOND 1000
#define COUT(msg) std::cout << msg << std::endl
using namespace std;

//volatile int lastCommand = 0;
//void on_command(const char* payload) {
//    printf("Befehl empfangen: %s\n", payload);
//    if (strcmp(payload, "start") == 0) {
//    	lastCommand = 1;
////        mqtt_festo_publish("festo/anlage1-2/status/Start", "1");
////        mqtt_festo_publish("festo/anlage1-2/console", "Anlage gestartet");
//    } else if (strcmp(payload, "stop") == 0) {
//    	lastCommand = 2;
////        mqtt_festo_publish("festo/anlage1-2/status/Start", "0");
////        mqtt_festo_publish("festo/anlage1-2/console", "Anlage gestoppt");
//    } else if (strcmp(payload, "notaus") == 0) {
//    	lastCommand = 3;
////        mqtt_festo_publish("festo/anlage1-2/status/Reset", "0");
////        mqtt_festo_publish("festo/anlage1-2/console", "NOT-AUS aktiviert");
//        // Hier ggf. deine eigentliche Notaus-Logik ergänzen!
//    } else if (strcmp(payload, "reset") == 0) {
//    	lastCommand = 4;
////        mqtt_festo_publish("festo/anlage1-2/status/Reset", "1");
////        mqtt_festo_publish("festo/anlage1-2/console", "Anlage zurückgesetzt");
//    } else {
//        //mqtt_festo_publish("festo/anlage1-2/console", "Unbekannter Befehl!");
//    }
//}



int main() {
  cout << "Starting Program..." << endl; // prints Hello World!!!
  system("gns -s ");

  Dispatcher* dispatcher = new Dispatcher();
  std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

  Thread_COM::Receiver* fsm_receiver = new Thread_COM::Receiver(FBM_2_FSM);
  Thread_COM::Sender* fsm_sender = new Thread_COM::Sender(FBM_2_DISPATCHER);

  Thread_COM::Sender* recorder_sender = new Thread_COM::Sender(FBM_2_DISPATCHER);

  //Thread_COM::Receiver* RemCon_receiver = new Thread_COM::Receiver(FBM_1_REMOTE); //comment this to test without RC
  Thread_COM::Sender* rc_sender = new Thread_COM::Sender(FBM_2_DISPATCHER);

  Thread_COM::Sender* com_sender_local = new Thread_COM::Sender(FBM_2_DISPATCHER);
  Thread_COM::Receiver* com_external_receiver = new Thread_COM::Receiver(FBM_2_COM);
  Thread_COM::Receiver* com_receiver_local = new Thread_COM::Receiver(FBM_2_COM_RECEIVER);

  Thread_COM::Receiver* hal_receiver = new Thread_COM::Receiver(FBM_2_HAL);
  Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_2_DISPATCHER);

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


  COM* externCommunication = new COM(com_external_receiver, FBM_1_COM, com_receiver_local, com_sender_local);
  externCommunication->start();

  // Thread_COM::Sender* senderDispatcher = new Thread_COM::Sender(FBM_2_DISPATCHER);
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

  cout << "Program Finished." << endl;
  return 0;


}
