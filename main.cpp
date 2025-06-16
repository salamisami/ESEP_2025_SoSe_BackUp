#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Event.h"
#include "ModeHandler.h"
#include "HAL.h"
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




	    HAL* hal = new HAL();
	    Remote_Controller* remCon = new Remote_Controller();

	    hal->test_ins();
	    delete hal;

	    // WAIT(3000);

	    // delete def;
	    // delete abc;

	    // delete hal_sender;
	    // delete fsm_sender;
	    // delete fsm_receiver;
	    // delete hal_receiver;

//	    while(1){
//
//	    }
//
//	    cout << "Program Finished." << endl;
//	    return 0;
//
//
//
//
//    bool fsm_running = true;
//    int eventNo = 0;
//    while(fsm_running) {
//        _pulse event;
//        fsm_receiver->receive_event(&event);
//        eventNo++;
//        printf("Event Number: %d\n", eventNo);
//        if((Topic) event.code == Topic::INTERRUPT && (InterruptEnum) event.value.sival_int == InterruptEnum::BUTTON_RESET_PRESSED){
//            fsm_running = false;
//        }
//        fsm->handleEvent(event);
//    }
//    printf("End of State.\n");
//
//    delete remCon;
//    delete fsm;
//    delete data;
//    delete timer_sender;
//
//    delete hal_sender;
//    delete fsm_sender;
//    delete fsm_receiver;
//    delete hal_receiver;
//
//    cout << "Program Finished." << endl;



	// setup MQTT client in synchronous mode

//
//	int rc = mqtt_festo_init("tcp://192.168.101.5:1883", "QNX_node_1");
//	if (rc != 0) {
//	    printf("MQTT init failed! Fehlercode: %d\n", rc);
//	    return 1;
//	}
//	    mqtt_festo_subscribe_command(on_command);
//
//	    // Beispiel: Initialstatus publishen
//	    mqtt_festo_publish("festo/anlage1/status/q1", "1");
//	    mqtt_festo_publish("festo/anlage1/status/q2", "1");
//	    mqtt_festo_publish("festo/anlage1/status/rutsche", "0");
//	    mqtt_festo_publish("festo/anlage2/status/rutsche", "0");
//	    mqtt_festo_publish("festo/anlage1/status/ampel", "red");
//	    mqtt_festo_publish("festo/anlage2/status/ampel", "red");
//	    mqtt_festo_publish("festo/anlage1-2/console", "BeagleBone bereit");
//
//	    // Hauptloop, z. B. Heartbeat und Statusmeldung
//	    while (1) {
//	        mqtt_festo_heartbeat();
//
//	        switch(lastCommand){
//				case 1: break;
//				case 2: break;
//				case 3: break;
//				case 4: break;
//	        }
//
//	        _pulse msg;
//			mock_dispatcher_receiver->receive_event(&msg);
//			ActuatorEnum event = (ActuatorEnum) msg.value.sival_int;
//			switch(event) {
//				case ActuatorEnum::LED_Q1_OFF:
//					mqtt_festo_publish("festo/anlage1/status/q1", "0");
//					break;
//				case ActuatorEnum::LED_Q1_ON:
//					mqtt_festo_publish("festo/anlage1/status/q1", "1");
//					break;
//				case ActuatorEnum::LED_Q2_OFF:
//					mqtt_festo_publish("festo/anlage1/status/q2", "0");
//					break;
//				case ActuatorEnum::LED_Q2_ON:
//					mqtt_festo_publish("festo/anlage1/status/q2", "1");
//					break;
//				case ActuatorEnum::TRAFFIC_GREEN_ON:
//					mqtt_festo_publish("festo/anlage1/status/ampel/green", "on");
//					break;
//				case ActuatorEnum::TRAFFIC_GREEN_OFF:
//					mqtt_festo_publish("festo/anlage1/status/ampel/green", "off");
//					break;
//				case ActuatorEnum::TRAFFIC_YELLOW_ON:
//					mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "on");
//					break;
//				case ActuatorEnum::TRAFFIC_YELLOW_OFF:
//					mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "off");
//					break;
//				case ActuatorEnum::TRAFFIC_RED_ON:
//					mqtt_festo_publish("festo/anlage1/status/ampel/red", "on");
//					break;
//				case ActuatorEnum::TRAFFIC_RED_OFF:
//					mqtt_festo_publish("festo/anlage1/status/ampel/red", "off");
//					break;
//				case ActuatorEnum::LED_START_ON:
//					mqtt_festo_publish("festo/anlage1/status/start", "1");
//					break;
//				case ActuatorEnum::LED_START_OFF:
//					mqtt_festo_publish("festo/anlage1/status/start", "0");
//					break;
//				case ActuatorEnum::LED_RESET_ON:
//					mqtt_festo_publish("festo/anlage1/status/reset", "1");
//					break;
//				case ActuatorEnum::LED_RESET_OFF:
//					mqtt_festo_publish("festo/anlage1/status/reset", "0");
//					break;
//			}
//
//	    }
//
//	    mqtt_festo_cleanup();
//


    return 0;
}
