/*
 * MQTT_Controller.h
 *
 *  Created on: 27.05.2025
 *      Author: robin
 */

#ifndef INC_MQTT_CONTROLLER_H_
#define INC_MQTT_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "./MQTTpaho/MQTTClient.h"

// Initialisierung und Verbindungsaufbau
int mqtt_festo_init(const char* broker, const char* client_id);

// Verbindung trennen
void mqtt_festo_cleanup(void);

// Senden von Status, Füllstand, etc.
int mqtt_festo_publish(const char* topic, const char* payload);

// Kommandos abonnieren
int mqtt_festo_subscribe_command(void (*command_callback)(const char* payload));

// Optional: Callback für weitere Topics (z.B. Reset, Start)
int mqtt_festo_subscribe(const char* topic, void (*cb)(const char* payload));

// Regelmäßigen Heartbeat senden
void mqtt_festo_heartbeat(void);

// ... weitere Funktionen nach Bedarf


#ifdef __cplusplus
}
#endif


#endif /* INC_MQTT_CONTROLLER_H_ */
