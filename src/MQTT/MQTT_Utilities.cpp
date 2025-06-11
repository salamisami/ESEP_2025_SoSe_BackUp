
#include "MQTT_Utilities.h"
MQTTClient MQTT_Utilities::client = nullptr;
static void (*g_command_callback)(const char* payload) = NULL;

// Helper
int MQTT_Utilities::mqtt_festo_publish(const char* topic, const char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    pubmsg.payload = (void*)payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 1;
    int rc = MQTTClient_publishMessage(MQTT_Utilities::client, topic, &pubmsg, &token);
    if (rc == MQTTCLIENT_SUCCESS) {
        MQTTClient_waitForCompletion(MQTT_Utilities::client, token, TIMEOUT);
    }
    return rc;
}

//int publishMsg(char * clientId, char * topic, char *payload){
//	MQTTClient_message pubmsg = MQTTClient_message_initializer;
//	MQTTClient_deliveryToken token;
//
//	pubmsg.payload = payload;
//	pubmsg.payloadlen = strlen(payload);
//	pubmsg.qos = QOS;
//	pubmsg.retained = 1;
//	int rc;
//
//	if ((rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token)) != MQTTCLIENT_SUCCESS) {
//		printf("Failed to publish topic %s (value = %s), return code %d\n", topic, payload, rc);
//		return rc;
//	};
//	printf("Waiting for up to %d seconds for publication of %s\n"
//	       "on topic %s for client with ClientID: %s\n",
//	       (int)(TIMEOUT/1000), payload, topic, clientId);
//	if ((rc = MQTTClient_waitForCompletion(client, token, TIMEOUT)) != MQTTCLIENT_SUCCESS) {
//		printf("Failed to publish topic %s (value = %s) - not completed, return code %d\n", topic, payload, rc);
//		return rc;
//	}
//	printf("Message with delivery token %d delivered\n", token);
//	return rc;
//}

static int internal_msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    if (strcmp(topicName, "festo/anlage1-2/command") == 0 && g_command_callback) {
        char payload[message->payloadlen+1];
        memcpy(payload, message->payload, message->payloadlen);
        payload[message->payloadlen] = '\0';
        g_command_callback(payload);
    }
    // weitere callbacks nach Bedarf
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int MQTT_Utilities::mqtt_festo_subscribe_command(void (*command_callback)(const char* payload)) {
    g_command_callback = command_callback;
    return MQTTClient_subscribe(client, "festo/anlage1-2/command", QOS);
}

int MQTT_Utilities::mqtt_festo_subscribe(const char* topic, void (*cb)(const char* payload)) {
    // Quick&Dirty: im internen Callback erweitern, z.B. per Hashmap wenn viele Topics
    // (siehe internal_msgarrvd)
    return MQTTClient_subscribe(client, topic, QOS);
}

void MQTT_Utilities::delivered(void *context, MQTTClient_deliveryToken dt) {}

void MQTT_Utilities::connlost(void *context, char *cause) {
    printf("MQTT Connection lost! Cause: %s\n", cause);
}

int MQTT_Utilities::mqtt_festo_init(const char* broker, const char* client_id) {
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

    MQTTClient_setCallbacks(client, NULL, MQTT_Utilities::connlost, internal_msgarrvd, MQTT_Utilities::delivered);
    rc = MQTTClient_connect(client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) return rc;

    // Beim Start als "online" markieren:
    //mqtt_festo_publish("festo/anlage1-2/status/online", "online");
    return 0;
}

void MQTT_Utilities::mqtt_festo_cleanup(void) {
	//mqtt_festo_publish("festo/anlage1-2/status/online", "offline");
	MQTTClient_disconnect(MQTT_Utilities::client, 10000);
	MQTTClient_destroy(&MQTT_Utilities::client);
}

void MQTT_Utilities::mqtt_festo_heartbeat(void) {
	//mqtt_festo_publish("festo/anlage1-2/status/online", "online");
}

//int connectClient(const char * brokerAdr, const char * clientId){
//	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
//	int rc;
//
//	if ((rc = MQTTClient_create(&client, brokerAdr, clientId,
//	    MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
//	    printf("Failed to create client, return code %d\n", rc);
//	    return rc;
//	}
//
//	if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS) {
//	        printf("Failed to set callbacks, return code %d\n", rc);
//	        MQTTClient_destroy(&client);
//	        return rc;
//	}
//
//	conn_opts.keepAliveInterval = 20;
//	conn_opts.cleansession = 1;
//	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
//		printf("Failed to connect, return code %d\n", rc);
//		MQTTClient_destroy(&client);
//		return rc;
//	}
//	return rc;
//}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    printf("Message arrived on topic: %s\n", topicName);
    // Annahme: Command-Topic
    if(strcmp(topicName, "festo/anlage1-2/command") == 0) {
        // Payload als String verarbeiten
        char cmd[32] = {0};
        strncpy(cmd, (char*)message->payload, message->payloadlen);
        cmd[message->payloadlen] = '\0';
        if(strcmp(cmd, "start") == 0) {
            // Starte Anlage
        } else if(strcmp(cmd, "stop") == 0) {
            // Stoppe Anlage
        } else if(strcmp(cmd, "notaus") == 0) {
            // Not-Aus auslösen
        } else if(strcmp(cmd, "reset") == 0) {
            // Anlage zurücksetzen
        } else {
            printf("Unbekannter Befehl: %s\n", cmd);
        }
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}





