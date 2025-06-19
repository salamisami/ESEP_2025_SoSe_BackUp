/*
 * RemoteController.cpp
 *
 *  Created on: 10.06.2025
 *      Author: robin
 */

#include "Remote_Controller.h"


std::queue<int> commandQueue;
std::mutex queueMutex;
std::condition_variable queueCV;
static void on_command(const char* payload);

Remote_Controller::Remote_Controller(I_Receiver* local_receiver, I_Sender* local_sender) {
    detached = false;
    this->local_receiver = local_receiver;
    this->local_sender = local_sender;
    init();
}

Remote_Controller::Remote_Controller()  {
    detached = true;
    local_receiver = new PulseMsg::Receiver();
    mock_dispatcher_receiver = new PulseMsg::Receiver();
    //TODO converting mock_dispatcher_Receiver to stack casues problem
    local_sender = new PulseMsg::Sender(mock_dispatcher_receiver->getchid());
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

Remote_Controller::~Remote_Controller() {
    mock_dispatcher_sender->send_event((int8_t) Topic::STOP_THREAD, 0);
    RemConThreadRecive.join();
    RemConThreadSend.join();

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
	//TODO automatische IP Zuweisung
	int rc = MQTT_Utilities::mqtt_festo_init("tcp://192.168.101.10:1883", ClientID);
		if (rc != 0) {
		    printf("MQTT init failed! Fehlercode: %d\n", rc);
		}

			MQTT_Utilities::mqtt_festo_subscribe_command(on_command);
			int subscribe_rc = MQTT_Utilities::mqtt_festo_subscribe_command(on_command);
			printf("Subscribe return code: %d\n", subscribe_rc);
		    // Beispiel: Initialstatus publishen
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q1", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/q2", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/start", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/reset", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/rutsche", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage2/status/rutsche", "0");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red", "off");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage2/status/ampel/red", "off");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "off");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage2/status/ampel/yellow", "off");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/green", "off");
			MQTT_Utilities::mqtt_festo_publish("festo/anlage2/status/ampel/green", "off");
			std::string msg = std::string(ClientID) + " is connected";
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
		    RemConThreadRecive = std::thread(&Remote_Controller::threadFunctionRecive, this);
		    RemConThreadSend = std::thread(&Remote_Controller::threadFunctionSend, this);
}

void Remote_Controller::threadFunctionRecive(){
	DEBUG("Remote Control Recive Thread started.");
	RemCon_recive_running = true;
	_pulse event;
	while (RemCon_recive_running) {
		//TODO Heartbeat
		MQTT_Utilities::mqtt_festo_heartbeat();
		int status = local_receiver->receive_event(&event);

		if(status == 0) {
			ActuatorEnum actuator_event_value = (ActuatorEnum) event.value.sival_int;
			InterruptEnum interrupt_event_value = (InterruptEnum) event.value.sival_int;
			//printf("[MQTT-DEBUG] Event empfangen: '%d'\n", event_value);
			Topic event_code = (Topic) event.code;
			if(event_code == Topic::ACTUATOR){
				switch(actuator_event_value) {
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
					case ActuatorEnum::TRAFFIC_GREEN_ON_FAST:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/green/1", "on");
						break;
					case ActuatorEnum::TRAFFIC_GREEN_ON_SLOW:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/green/0.5", "on");
						break;
					case ActuatorEnum::TRAFFIC_YELLOW_ON:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "on");
						break;
					case ActuatorEnum::TRAFFIC_YELLOW_OFF:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow", "off");
						break;
					case ActuatorEnum::TRAFFIC_YELLOW_ON_FAST:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow/1", "on");
						break;
					case ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/yellow/0.5", "on");
						break;
					case ActuatorEnum::TRAFFIC_RED_ON:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red", "on");
						break;
					case ActuatorEnum::TRAFFIC_RED_OFF:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red", "off");
						break;
					case ActuatorEnum::TRAFFIC_RED_ON_FAST:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red/1", "on");
						break;
					case ActuatorEnum::TRAFFIC_RED_ON_SLOW:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/ampel/red/0.5", "on");
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
					case ActuatorEnum::MOTOR_LEFT_START:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Motor startet in Linkslauf");
						break;
					case ActuatorEnum::MOTOR_RIGHT_START:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Motor startet in Rechtslauf");
						break;
					case ActuatorEnum::MOTOR_SLOW_OFF:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Motor langsam start");
						break;
					case ActuatorEnum::MOTOR_SLOW_ON:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Motor langsam stopp");
						break;
					case ActuatorEnum::MOTOR_STOP:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Motor stopp");
						break;
					case ActuatorEnum::SORTING_OFF:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Werkstück aussortieren");
						break;
					case ActuatorEnum::SORTING_ON:
						MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console","Werkstück einsortieren");
						break;

				}
			}
			if(event_code == Topic::INTERRUPT){
				if(interrupt_event_value == InterruptEnum::BUTTON_ESTOP_PRESSED){
					MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/notaus","true");
				}
				if(interrupt_event_value == InterruptEnum::BUTTON_ESTOP_RELEASED){
					MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/notaus","false");
				}
			}
		}
	}
}

void Remote_Controller::threadFunctionSend(){
	DEBUG("Remote Control Send Thread started.");
	RemCon_send_running = true;
	int8_t InterruptCode = (int8_t) Topic::INTERRUPT;
	//_pulse event;
	while (RemCon_send_running) {
		int command = 0;
		std::unique_lock<std::mutex> lock(queueMutex);
		queueCV.wait(lock, []{ return !commandQueue.empty(); }); // Warte auf neue Kommandos
		command = commandQueue.front();
		commandQueue.pop();
		switch(command){
			case 1:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_START_PRESSED);
					break;
			case 2:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_START_RELEASED);
					break;
			case 3:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_STOP_PRESSED);
					break;
			case 4:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_STOP_RELEASED);
					break;
			case 5:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_RESET_PRESSED);
					break;
			case 6:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_RESET_RELEASED);
					break;
			case 7:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_ESTOP_PRESSED);
					break;
			case 8:	local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_ESTOP_RELEASED);//TODO Eigener Remote E-Stop released
					break;
		}
	}
}

static void on_command(const char* payload) {
	printf("[MQTT-DEBUG] Payload empfangen: '%s'\n", payload, strlen(payload));
	int Last_Command = 0;
    if (strcmp(payload, "startPressed") == 0) {
    	Last_Command = 1;
    } else if (strcmp(payload, "startReleased") == 0) {
    	Last_Command = 2;
    } else if (strcmp(payload, "stopPressed") == 0) {
    	Last_Command = 3;
    } else if (strcmp(payload, "stopReleased") == 0) {
    	Last_Command = 4;
    } else if (strcmp(payload, "resetPressed") == 0) {
    	Last_Command = 5;
    } else if (strcmp(payload, "resetReleased") == 0) {
        Last_Command = 6;
    } else if (strcmp(payload, "true") == 0) {
        Last_Command = 7;
    } else if (strcmp(payload, "false") == 0) {
        Last_Command = 8;
    } else {
    	Last_Command = 0;
    	DEBUG("-1 erhalten");
    }
		std::lock_guard<std::mutex> lock(queueMutex);
		commandQueue.push(Last_Command);
        queueCV.notify_one();
}


