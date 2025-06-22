#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
#include "COM.h"
#include "Timer.h"
#include "Logic.h"
#include "Remote_Controller.h"
#include <iostream>
#include <unistd.h>

#include "inc/MQTT/MQTT_Utilities.h"
#define ONE_MILLISECOND 1000

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

    Thread_COM::Sender* com_dispatcher_sender = new Thread_COM::Sender(FBM_2_DISPATCHER);

    Thread_COM::Receiver* com_receiver = new Thread_COM::Receiver(FBM_2_COM); //empfängt andere Maschine
    Thread_COM::Receiver* com_dispatcher_receiver = new Thread_COM::Receiver(FBM_2_COM_RECEIVER); //empfängt lokalen dispatcher




    Thread_COM::Receiver* fsm_receiver = new Thread_COM::Receiver(FBM_1_FSM);
    Thread_COM::Sender* fsm_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);

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


    while(1) {

    }

    cout << "Program Finished." << endl;
    return 0;


}
