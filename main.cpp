#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Event.h"
#include "ModeHandler.h"
#include "HAL.h"
#include "MQTT_Controller.h"

#include <iostream>
#include <unistd.h>
#define ONE_MILLISECOND 1000

using namespace std;

volatile int lastCommand = 0;
void on_command(const char* payload) {
    printf("Befehl empfangen: %s\n", payload);
    if (strcmp(payload, "start") == 0) {
    	lastCommand = 1;
//        mqtt_festo_publish("festo/anlage1-2/status/Start", "1");
//        mqtt_festo_publish("festo/anlage1-2/console", "Anlage gestartet");
    } else if (strcmp(payload, "stop") == 0) {
    	lastCommand = 2;
//        mqtt_festo_publish("festo/anlage1-2/status/Start", "0");
//        mqtt_festo_publish("festo/anlage1-2/console", "Anlage gestoppt");
    } else if (strcmp(payload, "notaus") == 0) {
    	lastCommand = 3;
//        mqtt_festo_publish("festo/anlage1-2/status/Reset", "0");
//        mqtt_festo_publish("festo/anlage1-2/console", "NOT-AUS aktiviert");
        // Hier ggf. deine eigentliche Notaus-Logik ergänzen!
    } else if (strcmp(payload, "reset") == 0) {
    	lastCommand = 4;
//        mqtt_festo_publish("festo/anlage1-2/status/Reset", "1");
//        mqtt_festo_publish("festo/anlage1-2/console", "Anlage zurückgesetzt");
    } else {
        //mqtt_festo_publish("festo/anlage1-2/console", "Unbekannter Befehl!");
    }
}



int main() {
//    cout << "Starting Program..." << endl; // prints Hello World!!!
//
//    PulseMsg::Receiver* hal_receiver =  new PulseMsg::Receiver();
//    PulseMsg::Receiver* fsm_receiver = new PulseMsg::Receiver();
//
//    PulseMsg::Sender* fsm_sender = new PulseMsg::Sender(hal_receiver->getchid());
//    PulseMsg::Sender* hal_sender = new PulseMsg::Sender(fsm_receiver->getchid());
//
//
//    I_Sender* timer_sender = new PulseMsg::Sender(fsm_receiver->getchid());
//    ContextData* data = new ContextData(fsm_sender, fsm_receiver, timer_sender);
//    Context<ModeHandler>* fsm = new Context<ModeHandler>(data);
//
//    HAL* hal = new HAL(hal_receiver, hal_sender);
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
//    delete hal;
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


	int rc = mqtt_festo_init("tcp://192.168.101.5:1883", "QNX_node_1");
	if (rc != 0) {
	    printf("MQTT init failed! Fehlercode: %d\n", rc);
	    return 1;
	}
	    mqtt_festo_subscribe_command(on_command);

	    // Beispiel: Initialstatus publishen
	    mqtt_festo_publish("festo/anlage1/status/q1", "1");
	    mqtt_festo_publish("festo/anlage1/status/q2", "1");
	    mqtt_festo_publish("festo/anlage1/status/rutsche", "0");
	    mqtt_festo_publish("festo/anlage2/status/rutsche", "0");
	    mqtt_festo_publish("festo/anlage1/status/ampel", "red");
	    mqtt_festo_publish("festo/anlage2/status/ampel", "red");
	    mqtt_festo_publish("festo/anlage1-2/console", "BeagleBone bereit");

	    // Hauptloop, z. B. Heartbeat und Statusmeldung
	    while (1) {
	        mqtt_festo_heartbeat();

	        switch(lastCommand){
	        case 1: break;
	        case 2: break;
	        case 3: break;
	        case 4: break;
	        }

	        _pulse event;
	        while(hal_running) {
	        local_receiver->receive_event(&event);
			Topic event_code = (Topic) event.code;
			switch(event_code) {
				case Topic::ACTUATOR:
					actuator_mailbox->put(event);
					break;
				case Topic::ADC:
					adc_mailbox->put(event);
					break;
				case Topic::STOP_THREAD:
					hal_running = false;
					break;
				default:
					break;
			}
		}



	        mqtt_festo_publish("festo/anlage1-2/status/Q1", "1");
	        mqtt_festo_publish("festo/anlage1/status/ampel", "red");
	        sleep(1);
	        mqtt_festo_publish("festo/anlage2/status/ampel", "green");
	    }

	    mqtt_festo_cleanup();



    return 0;
}
