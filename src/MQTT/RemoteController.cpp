/*
 * RemoteController.cpp
 *
 *  Created on: 10.06.2025
 *      Author: robin
 */

#include "Remote_Controller.h"
#include <string>

std::queue<int> commandQueue;
static std::atomic<bool> dash_conn_lost;
std::mutex queueMutex;
std::mutex heartbeatMutex;

std::condition_variable queueCV;
static void on_command(const char* payload);
std::chrono::steady_clock::time_point last_dashboard_heartbeat;
std::atomic<bool> Remote_Controller::Main_running(true);

// Helper zum Zusammenbauen der Topics
inline std::string make_topic(const char* prefix, const char* suffix) {
    return std::string(prefix) + suffix;
}

Remote_Controller::Remote_Controller(I_Receiver* local_receiver, I_Sender* local_sender) {
    detached = false;
    this->local_receiver = local_receiver;
    this->local_sender = local_sender;
    init(false);
}

Remote_Controller::Remote_Controller() {
    detached = true;
    local_receiver = new PulseMsg::Receiver();
    mock_dispatcher_receiver = new PulseMsg::Receiver();
    local_sender = new PulseMsg::Sender(mock_dispatcher_receiver->getchid());
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init(false);
}

Remote_Controller::~Remote_Controller() {
    // 1. Stop-Flags setzen
    RemCon_recive_running = false;
    RemCon_send_running = false;
    RemCon_HeartCheck_running = false;
    MQTT_Utilities::connection_lost = true;

    //	    local_sender->send_event((int8_t) Topic::WAKE_UP,0);
    //		if (RemConThreadRecive.joinable()) RemConThreadRecive.join();
    //		queueCV.notify_all();
    //		if (RemConThreadSend.joinable()) RemConThreadSend.join();
    //		if (RemConThreadHeartBeat.joinable()) RemConThreadHeartBeat.join();

            // 4. Threads joinen (warten bis sie beendet sind)
    //	    if (RemConThreadRecive.joinable())
    //	        RemConThreadRecive.join();
    //	    if (RemConThreadSend.joinable())
    //	        RemConThreadSend.join();
    if(RemConThreadHeartBeat.joinable())
        RemConThreadHeartBeat.join();

    // 5. Ressourcen freigeben
    if(detached) {
        delete mock_dispatcher_sender;
        delete local_sender;
        delete mock_dispatcher_receiver;
        delete local_receiver;
    } else {
        delete mock_dispatcher_sender;
    }

    // 6. MQTT aufräumen
    //MQTT_Utilities::mqtt_festo_cleanup();
}

void Remote_Controller::init(bool reInit) {
    bool mqtt_connected = false;
    int rc = 0;

    while(!mqtt_connected) {
        rc = MQTT_Utilities::mqtt_festo_init("tcp://192.168.101.7:1883", ClientID);
        if(rc != 0) {
            printf("MQTT init failed! Fehlercode: %d\n", rc);
            MQTT_Utilities::mqtt_festo_cleanup();
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }
        mqtt_connected = true;
        last_dashboard_heartbeat = std::chrono::steady_clock::now();
    }

    int subscribe_rc = MQTT_Utilities::mqtt_festo_subscribe_command(on_command);
    printf("Subscribe return code: %d\n", subscribe_rc);

    // Initialstatus publishen:
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "q1").c_str(), "0");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "q2").c_str(), "0");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "start").c_str(), "0");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "reset").c_str(), "0");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "rutsche").c_str(), "0");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/red").c_str(), "off");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/yellow").c_str(), "off");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/green").c_str(), "off");
    MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "notaus").c_str(), "false");

    std::string msgClient = std::string(ClientID) + ": is connected ";
    MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msgClient.c_str());

    RemConThreadRecive = std::thread(&Remote_Controller::threadFunctionRecive, this);
    RemConThreadSend = std::thread(&Remote_Controller::threadFunctionSend, this);

    if(!reInit) {
        RemConThreadHeartBeat = std::thread(&Remote_Controller::threadFunctionHeartbeat, this);
    }
    int8_t RemConCode = (int8_t) Topic::REM_CON;
    local_sender->send_event(RemConCode, (int) RemoteControlEnum::MQTT_CONNECTED);
}

void Remote_Controller::threadFunctionRecive() {
    DEBUG("Remote Control Recive Thread started.");
    RemCon_recive_running = true;
    _pulse event;
    while(RemCon_recive_running && !MQTT_Utilities::connection_lost) {
        int status = local_receiver->receive_event(&event);
        int rc = MQTTClient_isConnected(MQTT_Utilities::client);
        if(rc != 0) {
            if(status == 0) {
                ActuatorEnum actuator_event_value = (ActuatorEnum) event.value.sival_int;
                InterruptEnum interrupt_event_value = (InterruptEnum) event.value.sival_int;
                Error_Enum Error_event_value = (Error_Enum) event.value.sival_int;
                Internal_Enum Internal_event_value = (Internal_Enum) event.value.sival_int;
                Topic event_code = (Topic) event.code;
                if(event_code == Topic::ACTUATOR) {
                    switch(actuator_event_value) {
                        case ActuatorEnum::LED_Q1_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "q1").c_str(), "0");
                            break;
                        case ActuatorEnum::LED_Q1_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "q1").c_str(), "1");
                            break;
                        case ActuatorEnum::LED_Q2_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "q2").c_str(), "0");
                            break;
                        case ActuatorEnum::LED_Q2_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "q2").c_str(), "1");
                            break;
                        case ActuatorEnum::TRAFFIC_GREEN_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/green").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_GREEN_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/green").c_str(), "off");
                            break;
                        case ActuatorEnum::TRAFFIC_GREEN_ON_FAST:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/green/1").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_GREEN_ON_SLOW:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/green/0.5").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_YELLOW_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/yellow").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_YELLOW_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/yellow").c_str(), "off");
                            break;
                        case ActuatorEnum::TRAFFIC_YELLOW_ON_FAST:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/yellow/1").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/yellow/0.5").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_RED_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/red").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_RED_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/red").c_str(), "off");
                            break;
                        case ActuatorEnum::TRAFFIC_RED_ON_FAST:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/red/1").c_str(), "on");
                            break;
                        case ActuatorEnum::TRAFFIC_RED_ON_SLOW:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "ampel/red/0.5").c_str(), "on");
                            break;
                        case ActuatorEnum::LED_START_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "start").c_str(), "1");
                            break;
                        case ActuatorEnum::LED_START_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "start").c_str(), "0");
                            break;
                        case ActuatorEnum::LED_RESET_ON:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "reset").c_str(), "1");
                            break;
                        case ActuatorEnum::LED_RESET_OFF:
                            MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "reset").c_str(), "0");
                            break;
                            //                        case ActuatorEnum::MOTOR_LEFT_START:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Motor startet in Linkslauf");
                            //                            break;
                            //                        case ActuatorEnum::MOTOR_RIGHT_START:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Motor startet in Rechtslauf");
                            //                            break;
                            //                        case ActuatorEnum::MOTOR_SLOW_OFF:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Motor langsam start");
                            //                            break;
                            //                        case ActuatorEnum::MOTOR_SLOW_ON:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Motor langsam stopp");
                            //                            break;
                            //                        case ActuatorEnum::MOTOR_STOP:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Motor stopp");
                            //                            break;
                            //                        case ActuatorEnum::SORTING_OFF:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Werkstück aussortieren");
                            //                            break;
                            //                        case ActuatorEnum::SORTING_ON:
                            //                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console",msgClient+"Werkstück einsortieren");
                            //                            break;
                        default:
                            break;
                    }
                }
                if(event_code == Topic::INTERRUPT) {
                    if(interrupt_event_value == InterruptEnum::BUTTON_ESTOP_PRESSED) {
                        MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "notaus").c_str(), "true");
                    }
                    if(interrupt_event_value == InterruptEnum::BUTTON_ESTOP_RELEASED) {
                        MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "notaus").c_str(), "false");
                    }
                }
                if(event_code == Topic::INTERNAL) {
                    if(Internal_event_value == Internal_Enum::RAMP_FULL) {
                        MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC, "rutsche").c_str(), "1");
                    }
                    if(Internal_event_value == Internal_Enum::RAMP_NOT_FULL) {
                        MQTT_Utilities::mqtt_festo_publish(make_topic(RECEIVE_TOPIC,"rutsche").c_str(),"0");
                    }
                }
                if(event_code == Topic::ERROR) {
                    std::string msg = "";
                    switch(Error_event_value) {
                        case Error_Enum::CANT_FIND_CALB_CONF:
                            msg = std::string(ClientID) + "Es konnte keine Kalibrierungsdatei gefunden werden";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::CANT_FIND_REP_CONF:
                            msg = std::string(ClientID) + "Es konnte keine Replaydatei gefunden werden!";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::ERROR_BOTH_R_FULL:
                            msg = std::string(ClientID) + "Achtung beide Rampen Sind Voll bitte leeren!";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::ERROR_C_LOST_COM:
                            msg = std::string(ClientID) + "Hat Keine Verbindung zur anderen Anlage!";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::ERROR_C_LOST_MQTT:
                            msg = std::string(ClientID) + "MQTT Verbindung verloren!";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::ERROR_C_LOST_NR:
                            msg = std::string(ClientID) + "?";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::ERROR_INVALID_MESURE:
                            msg = std::string(ClientID) + "Ungültige Höhenmessung!";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        case Error_Enum::ERROR_W_LOST:
                            msg = std::string(ClientID) + "Ein Werkstück ist verschwunden!";
                            MQTT_Utilities::mqtt_festo_publish("festo/anlage1-2/console", msg.c_str());
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}




void Remote_Controller::threadFunctionSend() {
    DEBUG("Remote Control Send Thread started.");
    RemCon_send_running = true;
    int8_t InterruptCode = (int8_t) Topic::INTERRUPT;
    int8_t RecReplayCode = (int8_t) Topic::REC_REPLAY;
    int8_t RemoteCode = (int8_t) Topic::REM_CON;
    while(RemCon_send_running && !MQTT_Utilities::connection_lost) {
        int command = 0;
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, [] {
            return !commandQueue.empty() || MQTT_Utilities::connection_lost || dash_conn_lost;
            });
        if(MQTT_Utilities::connection_lost || dash_conn_lost) break;
        if(commandQueue.empty()) continue;
        command = commandQueue.front();
        commandQueue.pop();
        switch(command) {
            case 1: local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_START_PRESSED); break;
            case 2: local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_START_RELEASED); break;
            case 3: local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_STOP_PRESSED); break;
            case 4: local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_STOP_RELEASED); break;
            case 5: local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_RESET_PRESSED); break;
            case 6: local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_RESET_RELEASED); break;
            case 7: local_sender->send_event(RemoteCode, (int) RemoteControlEnum::REMOTE_ESTOP); break;
                //            case 8: //local_sender->send_event(InterruptCode, (int) InterruptEnum::BUTTON_ESTOP_RELEASED); break;
                //            		break;
            case 9: local_sender->send_event(RecReplayCode, (int) RecReplayEnum::START_REC); break;
            case 10: local_sender->send_event(RecReplayCode, (int) RecReplayEnum::STOP_REC); break;
            case 11: local_sender->send_event(RecReplayCode, (int) RecReplayEnum::START_REPLAY); break;
            case 12: local_sender->send_event(RecReplayCode, (int) RecReplayEnum::STOP_REPLAY); break;
            case 13: Remote_Controller::Main_running = false; break;
        }
    }
}

void Remote_Controller::threadFunctionHeartbeat() {
    RemCon_HeartCheck_running = true;


    while(RemCon_HeartCheck_running) {

        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_dashboard_heartbeat).count();

        if(diff > HEARTBEAT_TIMEOUT_MS) {
            dash_conn_lost = true;
        } else {
            dash_conn_lost = false;
        }

        if(MQTT_Utilities::connection_lost || dash_conn_lost) {
            DEBUG("Connection lost detected. Cleaning up ...\n");
            RemCon_send_running = false;
            RemCon_recive_running = false;

            local_sender->send_event((int8_t) Topic::WAKE_UP, 0);
            if(RemConThreadRecive.joinable()) RemConThreadRecive.join();
            queueCV.notify_all();
            if(RemConThreadSend.joinable()) RemConThreadSend.join();

            int8_t RemConCode = (int8_t) Topic::REM_CON;
            //local_sender->send_event(RemConCode, (int) RemoteControlEnum::MQTT_DISCONNECTED);

            MQTTClient_disconnect(MQTT_Utilities::client, 1000);
            MQTTClient_destroy(&MQTT_Utilities::client);
            MQTT_Utilities::client = nullptr;

            DEBUG("Waiting for reconnect command ...\n");
            bool reconnect = false;
            while(!reconnect) {
                //                _pulse event;
                //                int status = local_receiver->receive_event(&event);
                //                RemoteControl event_value = (RemoteControl) event.value.sival_int;
                //                Topic event_code = (Topic) event.code;
                //                if (status == 0 && event_code == Topic::REM_CON) {
                //                    if(event_value == RemoteControl::RECONNECT)
                //                        reconnect = true;
                //                    DEBUG("Reconnect command received!\n");
                //                }
                                //nur zum testen
                std::this_thread::sleep_for(std::chrono::seconds(3));
                reconnect = true;
            }
            MQTT_Utilities::connection_lost = false;
            dash_conn_lost = false;
            if(RemCon_HeartCheck_running) {
                init(true);
            }
        } else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

static void on_command(const char* payload) {
    if(!payload) {
        printf("[MQTT-DEBUG] Warning: Received null payload in on_command\n");
        return;
    }
    size_t len = strnlen(payload, 128);
    if(len == 0) {
        printf("[MQTT-DEBUG] Warning: Received empty payload in on_command\n");
        return;
    }
    //printf("[MQTT-DEBUG] Payload empfangen: '%.*s'\n", (int)len, payload);
    int Last_Command = 0;
    if(strncmp(payload, "startPressed", len) == 0) {
        Last_Command = 1;
    } else if(strncmp(payload, "startReleased", len) == 0) {
        Last_Command = 2;
    } else if(strncmp(payload, "stopPressed", len) == 0) {
        Last_Command = 3;
    } else if(strncmp(payload, "stopReleased", len) == 0) {
        Last_Command = 4;
    } else if(strncmp(payload, "resetPressed", len) == 0) {
        Last_Command = 5;
    } else if(strncmp(payload, "resetReleased", len) == 0) {
        Last_Command = 6;
    } else if(strncmp(payload, "true", len) == 0) {
        Last_Command = 7;
    } else if(strncmp(payload, "false", len) == 0) {
        Last_Command = 8;
    } else if(strncmp(payload, "RecStart", len) == 0) {
        Last_Command = 9;
    } else if(strncmp(payload, "RecStop", len) == 0) {
        Last_Command = 10;
    } else if(strncmp(payload, "RepStart", len) == 0) {
        Last_Command = 11;
    } else if(strncmp(payload, "RepStop", len) == 0) {
        Last_Command = 12;
    } else if(strncmp(payload, "softstop", len) == 0) {
        Last_Command = 13;
    } else if(strncmp(payload, "HeartBeat", len) == 0) {
        last_dashboard_heartbeat = std::chrono::steady_clock::now();
        dash_conn_lost = false; // Optional, wenn du sicher bist, dass wieder Kontakt besteht.
        return;
    } else {
        Last_Command = 0;
        printf("[MQTT-DEBUG] Unbekannter Payload erhalten: '%.*s'\n", (int) len, payload);
    }
    {
        std::lock_guard<std::mutex>lock(queueMutex);
        commandQueue.push(Last_Command);
    }
    queueCV.notify_one();
}
