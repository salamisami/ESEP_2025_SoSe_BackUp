#include "MQTT_Controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static MQTTClient client;
static void (*g_command_callback)(const char* payload) = NULL;

#define QOS 1
#define TIMEOUT 10000L

// Helper
int mqtt_festo_publish(const char* topic, const char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    pubmsg.payload = (void*)payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 1;
    int rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    if (rc == MQTTCLIENT_SUCCESS) {
        MQTTClient_waitForCompletion(client, token, TIMEOUT);
    }
    return rc;
}

static int internal_msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    if (strcmp(topicName, "festo/anlage1-2/command") == 0 && g_command_callback) {
        char payload[message->payloadlen+1];
        memcpy(payload, message->payload, message->payloadlen);
        payload[message->payloadlen] = '\0';
        g_command_callback(payload);
    }
    // weitere callbacks nach Bedarf...
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int mqtt_festo_subscribe_command(void (*command_callback)(const char* payload)) {
    g_command_callback = command_callback;
    return MQTTClient_subscribe(client, "festo/anlage1-2/command", QOS);
}

int mqtt_festo_subscribe(const char* topic, void (*cb)(const char* payload)) {
    // Quick&Dirty: im internen Callback erweitern, z.B. per Hashmap wenn viele Topics
    // (siehe internal_msgarrvd)
    return MQTTClient_subscribe(client, topic, QOS);
}

void delivered(void *context, MQTTClient_deliveryToken dt) {}

void connlost(void *context, char *cause) {
    printf("MQTT Connection lost! Cause: %s\n", cause);
}

int mqtt_festo_init(const char* broker, const char* client_id) {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_willOptions will_opts = MQTTClient_willOptions_initializer;
    int rc;

    will_opts.topicName = "festo/anlage1-2/status/online";
    will_opts.message   = "offline";
    will_opts.qos       = 1;
    will_opts.retained  = 1;
    conn_opts.will = &will_opts;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    rc = MQTTClient_create(&client, broker, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if (rc != MQTTCLIENT_SUCCESS) return rc;

    MQTTClient_setCallbacks(client, NULL, connlost, internal_msgarrvd, delivered);
    rc = MQTTClient_connect(client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) return rc;

    // Beim Start als "online" markieren:
    mqtt_festo_publish("festo/anlage1-2/status/online", "online");
    return 0;
}

void mqtt_festo_cleanup(void) {
    mqtt_festo_publish("festo/anlage1-2/status/online", "offline");
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}

void mqtt_festo_heartbeat(void) {
    mqtt_festo_publish("festo/anlage1-2/status/online", "online");
}





