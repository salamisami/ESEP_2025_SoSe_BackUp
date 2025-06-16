/*
 * RemoteController.cpp
 *
 *  Created on: 10.06.2025
 *      Author: robin
 */

#include "Remote_Controller.h"
volatile int Last_Command;
static void on_command(const char* payload);

Remote_Controller::Remote_Controller(I_Receiver* local_receiver, I_Sender* local_sender) {
    detached = false;
    //Last_Command = 0;
    this->local_receiver = local_receiver;
    this->local_sender = local_sender;
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

Remote_Controller::Remote_Controller()  {
    detached = true;
    //Last_Command = 0;
    local_receiver = new PulseMsg::Receiver();
    mock_dispatcher_receiver = new PulseMsg::Receiver();
    //TODO converting mock_dispatcher_Receiver to stack casues problem
    local_sender = new PulseMsg::Sender(mock_dispatcher_receiver->getchid());
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

Remote_Controller::~Remote_Controller() {
    mock_dispatcher_sender->send_event((int8_t) Topic::STOP_THREAD, 0);
    RemConThread.join();
    //DEBUG("Actuator and Interrupts are deleted");
    if(detached) {
        delete mock_dispatcher_sender;
        delete local_sender;
        delete mock_dispatcher_receiver;
        delete local_receiver;
    } else {
        delete mock_dispatcher_sender;
    }
}

void Remote_Controller::init() {

	int rc = MQTT_Utilities::mqtt_festo_init("tcp://192.168.101.10:1883", "QNX_node_1");
		if (rc != 0) {
		    printf("MQTT init failed! Fehlercode: %d\n", rc);
		}

			MQTT_Utilities::mqtt_festo_subscribe_command(on_command);

		    // Beispiel: Initialstatus publishen
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q1", "1");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q2", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/rutsche", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage2/status/rutsche", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel", "red");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage2/status/ampel", "red");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", "BeagleBone bereit");
		    RemConThread = std::thread(&Remote_Controller::threadFunction, this);
}

void Remote_Controller::threadFunction(){
	DEBUG("Remote Control Thread started.");
	RemCon_running = true;
	_pulse event;
	while (RemCon_running) {
		MQTT_Utilities::mqtt_festo_heartbeat();

		switch(Last_Command){
			case 1:DEBUG("1 erhalten");break;
			case 2:DEBUG("2 erhalten"); break;
			case 3:DEBUG("3 erhalten"); break;
			case 4:DEBUG("4 erhalten"); break;
		}
		_pulse msg;
		mock_dispatcher_receiver->receive_event(&msg);
		ActuatorEnum event = (ActuatorEnum) msg.value.sival_int;
		switch(event) {
			case ActuatorEnum::LED_Q1_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q1", "0");
				break;
			case ActuatorEnum::LED_Q1_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q1", "1");
				break;
			case ActuatorEnum::LED_Q2_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q2", "0");
				break;
			case ActuatorEnum::LED_Q2_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q2", "1");
				break;
			case ActuatorEnum::TRAFFIC_GREEN_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/green", "on");
				break;
			case ActuatorEnum::TRAFFIC_GREEN_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/green", "off");
				break;
			case ActuatorEnum::TRAFFIC_YELLOW_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "on");
				break;
			case ActuatorEnum::TRAFFIC_YELLOW_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "off");
				break;
			case ActuatorEnum::TRAFFIC_RED_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red", "on");
				break;
			case ActuatorEnum::TRAFFIC_RED_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red", "off");
				break;
			case ActuatorEnum::LED_START_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/start", "1");
				break;
			case ActuatorEnum::LED_START_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/start", "0");
				break;
			case ActuatorEnum::LED_RESET_ON:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/reset", "1");
				break;
			case ActuatorEnum::LED_RESET_OFF:
				MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/reset", "0");
				break;
		}

	}
}

static void on_command(const char* payload) {
    ("Befehl empfangen: %s\n", payload);
    if (strcmp(payload, "start") == 0) {
    	Last_Command = 1;
    } else if (strcmp(payload, "stop") == 0) {
    	Last_Command = 2;
    } else if (strcmp(payload, "notaus") == 0) {
    	Last_Command = 3;
    } else if (strcmp(payload, "reset") == 0) {
    	Last_Command = 4;
    } else {
    	Last_Command = -1;
    }
}

//void Remote_Controller::test_ins() {
//    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
//    bool running = true;
//    int8_t actuatorCode = (int8_t) Topic::ACTUATOR;
//    bool allowGo = true;
//    bool allowSorting = true;
//    while(running) {
//        _pulse msg;
//        mock_dispatcher_receiver->receive_event(&msg);
//        InterruptEnum event = (InterruptEnum) msg.value.sival_int;
//        switch(event) {
//            case InterruptEnum::LASER_FRONT_BLOCKED:
//                std::cout << "Thanks!" << std::endl;
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
//                if(allowGo) {
//                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_RIGHT_START);
//                }
//                break;
//            case InterruptEnum::LASER_BACK_BLOCKED:
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_STOP);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_ON);
//                allowGo = false;
//                break;
//            case InterruptEnum::LASER_BACK_UNBLOCKED:
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_OFF);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
//                allowGo = true;
//                break;
//            case InterruptEnum::LASER_SORTING_GATE_BLOCKED:
//                if(!allowSorting) {
//                    break;
//                }
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_ON);
//                WAIT(1000);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_OFF);
//                break;
//            case InterruptEnum::BUTTON_ESTOP_PRESSED:
//                //running = false;
//                break;
//            case InterruptEnum::BUTTON_STOP_PRESSED:
//                running = false;
//                break;
//            case InterruptEnum::ADC_TOP_AREA_BLOCKED:
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_ON);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
//                break;
//            case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
//                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
//                break;
//            case InterruptEnum::LASER_RAMP_BLOCKED:
//                allowSorting = false;
//                break;
//            case InterruptEnum::LASER_RAMP_UNBLOCKED:
//                allowSorting = true;
//                break;
//            default:
//                break;
//        }
//    }
//    std::cout << "Testing Input done." << std::endl;
//}
