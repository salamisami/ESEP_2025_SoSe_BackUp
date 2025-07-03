/*
 * MQTT_Utilities.h
 *
 *  Created on: 27.05.2025
 *      Author: robin
 */

#ifndef MQTT_UTILITIES_H
#define MQTT_UTILITIES_H
#include "MQTTClient.h"
#include "Thread_COM.h"
#include <unistd.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <atomic>


// Kein extern "C" notwendig, da du C++ verwendest


#define BROKER_ADR        "tcp://192.168.101.5:1883"
#define NO_OF_TOPICS      10
#define NO_OF_ITERATIONS  4
#define STR_BUF_SIZE      100
#define QOS               1
#define TIMEOUT           10000L
#define ClientID		MQTT_CLIENT


class MQTT_Utilities{
public:
	static MQTTClient client;
    MQTT_Utilities() = delete;
    MQTT_Utilities(const MQTT_Utilities&) = delete;
    MQTT_Utilities& operator = (const MQTT_Utilities&) = delete;
    virtual ~MQTT_Utilities() = delete;


    static std::atomic<bool> connection_lost;

    // Initialisierung und Verbindungsaufbau
    static int mqtt_festo_init(const char* broker, const char* client_id);

    // Verbindung trennen
    static void mqtt_festo_cleanup(void);

    // Senden von Status, Füllstand, etc.
    static int mqtt_festo_publish(const char* topic, const char* payload);

    // Kommandos abonnieren
    static int mqtt_festo_subscribe_command(void (*command_callback)(const char* payload));

    // Optional: Callback für weitere Topics (z.B. Reset, Start)
    static int mqtt_festo_subscribe(const char* topic, void (*cb)(const char* payload));

    // Regelmäßigen Heartbeat senden
    static void mqtt_festo_heartbeat(void);

    static void delivered(void *context, MQTTClient_deliveryToken dt);

    static void connlost(void *context, char *cause);

    static int internal_msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);

private:

    //static void (*g_command_callback)(const char* payload) = NULL;
    //static int atLeastOneTopicArrived;
};

#endif // MQTT_UTILITIES_H
