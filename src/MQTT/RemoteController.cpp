/*
 * RemoteController.cpp
 *
 *  Created on: 10.06.2025
 *      Author: robin
 */

#include "Remote_Controller.h"


std::queue<int> commandQueue;
static std::atomic<bool> dash_conn_lost;
std::mutex queueMutex;
std::mutex heartbeatMutex;

std::condition_variable queueCV;
static void on_command(const char* payload);
//static void (*g_command_callback)(const char* payload) = NULL;
//static void connlost_static(void *context, char *cause);
//static int internal_msgarrvd_static(void *context, char *topicName, int topicLen, MQTTClient_message *message);
//static void delivered_static(void *context, MQTTClient_deliveryToken dt);
std::chrono::steady_clock::time_point last_heartbeat = std::chrono::steady_clock::now();



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
    RemConThreadHeartBeat.join();

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
	int rc = MQTT_Utilities::mqtt_festo_init("tcp://192.168.101.5:1883", ClientID);
		if (rc != 0) {
		    printf("MQTT init failed! Fehlercode: %d\n", rc);
		}

			int subscribe_rc = MQTT_Utilities::mqtt_festo_subscribe_command(on_command);
			printf("Subscribe return code: %d", subscribe_rc);
			//MQTT_Utilities::connection_lost = false;
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
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1/status/notaus","false");
			std::string msg = std::string(ClientID) + " is connected";
			MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
		    RemConThreadRecive = std::thread(&Remote_Controller::threadFunctionRecive, this);
		    RemConThreadSend = std::thread(&Remote_Controller::threadFunctionSend, this);
		    RemConThreadHeartBeat = std::thread(&Remote_Controller::threadFunctionHeartbeat, this);
}

void Remote_Controller::threadFunctionRecive(){
	DEBUG("Remote Control Recive Thread started.");
	RemCon_recive_running = true;
	_pulse event;
	while (RemCon_recive_running && !MQTT_Utilities::connection_lost ) {
		//TODO Heartbeat
		//MQTT_Utilities::mqtt_festo_heartbeat();
		int status = local_receiver->receive_event(&event);
		int rc = MQTTClient_isConnected(MQTT_Utilities::client);
		if (rc != 0){
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
}

void Remote_Controller::threadFunctionSend(){
	DEBUG("Remote Control Send Thread started.");
	RemCon_send_running = true;
	int8_t InterruptCode = (int8_t) Topic::INTERRUPT;
	int8_t RecReplayCode = (int8_t) Topic::REC_REPLAY;
	//_pulse event;
	while (RemCon_send_running && !MQTT_Utilities::connection_lost) {
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
			case 9:	local_sender->send_event(RecReplayCode, (int) RecReplayEnum::START_REC);
					break;
			case 10:local_sender->send_event(RecReplayCode, (int) RecReplayEnum::STOP_REC);
					break;
			case 11:local_sender->send_event(RecReplayCode, (int) RecReplayEnum::START_REPLAY);
					break;
			case 12:local_sender->send_event(RecReplayCode, (int) RecReplayEnum::STOP_REPLAY);
					break;
		}
	}

}

void Remote_Controller::threadFunctionHeartbeat() {
	RemCon_HeartCheck_running = true;
    while (RemCon_HeartCheck_running) {
        // Überwache beide Verbindungen
        if (MQTT_Utilities::connection_lost || dash_conn_lost) {
            printf("Connection lost detected. Cleaning up ...\n");

            // Stoppe alle Sender/Receiver-Threads!
            RemCon_send_running = false;
            RemCon_recive_running = false;

            int8_t AcuatorCode = (int8_t) Topic::ACTUATOR;
            local_sender->send_event(AcuatorCode, (int) ActuatorEnum::WAKE_UP);

            if (RemConThreadRecive.joinable()) RemConThreadRecive.join();
            if (RemConThreadSend.joinable()) RemConThreadSend.join();

            // MQTT sauber beenden
            MQTTClient_disconnect(MQTT_Utilities::client, 1000);
            MQTTClient_destroy(&MQTT_Utilities::client);
            MQTT_Utilities::client = nullptr;

            // Warten auf Reconnect-Befehl
            printf("Waiting for reconnect command ...\n");
            bool reconnect = false;
            while (!reconnect) {
//                // Empfange event mit lokalem Receiver, z.B.
//                _pulse event;
//                int status = local_receiver->receive_event(&event);
//                RemoteControl event_value = (RemoteControl) event.value.sival_int;
//                Topic event_code = (Topic) event.code;
//                if (status == 0 && event_code == Topic::REM_CON) {
//                	if(event_value == RemoteControl::RECONNECT)
//                    reconnect = true;
//                    printf("Reconnect command received!\n");
//                }
                std::this_thread::sleep_for(std::chrono::seconds(10));
                reconnect = true;
            }

            // Flags zurücksetzen, wenn nötig
            MQTT_Utilities::connection_lost = false;
            dash_conn_lost = false;

            // Neu initialisieren (startet alle Threads, MQTT etc.)
            init();
        } else {
            // Alles OK: Herzschlag
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}


static void on_command(const char* payload) {
	// 1. Null-Check und minimale Länge prüfen
	    if (!payload) {
	        printf("[MQTT-DEBUG] Warning: Received null payload in on_command\n");
	        return;
	    }

	    // Optional: Defensive strlen, capped auf sinnvolle Länge
	    size_t len = strnlen(payload, 128); // max 128 chars
	    if (len == 0) {
	        printf("[MQTT-DEBUG] Warning: Received empty payload in on_command\n");
	        return;
	    }

	    printf("[MQTT-DEBUG] Payload empfangen: '%.*s'\n", (int)len, payload);

	    int Last_Command = 0;
	    if (strncmp(payload, "startPressed", len) == 0) {
	        Last_Command = 1;
	    } else if (strncmp(payload, "startReleased", len) == 0) {
	        Last_Command = 2;
	    } else if (strncmp(payload, "stopPressed", len) == 0) {
	        Last_Command = 3;
	    } else if (strncmp(payload, "stopReleased", len) == 0) {
	        Last_Command = 4;
	    } else if (strncmp(payload, "resetPressed", len) == 0) {
	        Last_Command = 5;
	    } else if (strncmp(payload, "resetReleased", len) == 0) {
	        Last_Command = 6;
	    } else if (strncmp(payload, "true", len) == 0) {
	        Last_Command = 7;
	    } else if (strncmp(payload, "false", len) == 0) {
	        Last_Command = 8;
	    } else if (strncmp(payload, "RecStart", len) == 0) {
	        Last_Command = 9;
	    } else if (strncmp(payload, "RecStop", len) == 0) {
	        Last_Command = 10;
	    } else if (strncmp(payload, "RepStart", len) == 0) {
	        Last_Command = 11;
	    } else if (strncmp(payload, "RepStop", len) == 0) {
	        Last_Command = 12;
	    } else if (strncmp(payload, "HeartBeat", len) == 0) {
	        Last_Command = 13;
	        dash_conn_lost = false;
	    } else {
	        Last_Command = 0;
	        printf("[MQTT-DEBUG] Unbekannter Payload erhalten: '%.*s'\n", (int)len, payload);
	    }

	    // 2. Thread-safe Einfügen in Queue
	    {
	        std::lock_guard<std::mutex> lock(queueMutex);
	        commandQueue.push(Last_Command);
	    }
	    queueCV.notify_one();
}




