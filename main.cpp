#include <iostream>
#include "Dispatcher.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include "DispatcherEvents.h"

int main(){
	system("gns -s ");
	Dispatcher *dispatcher = new Dispatcher();
	std::thread disp(&Dispatcher::start_dispatcher, dispatcher);
	printf("Dispatcher started \n");

	name_attach_t *m_hal;
	name_attach_t *m_fsm;
	name_attach_t *m_qnet;
	name_attach_t *m_mqtt;

	int rcid_m_hal;
	int rcid_m_fsm;
	int rcid_m_qnet;
	int rcid_m_mqtt;

	typedef struct _pulse header_t;
	header_t header;

	m_hal = name_attach(NULL, "HAL", NAME_FLAG_ATTACH_GLOBAL);
	printf("Mock Hal started\n");
	m_fsm = name_attach(NULL, "FSM", NAME_FLAG_ATTACH_GLOBAL);
	printf("Mock Fsm started\n");
	m_qnet = name_attach(NULL, "QNET", NAME_FLAG_ATTACH_GLOBAL);
	printf("Mock Qnet started\n");
	m_mqtt = name_attach(NULL, "MQTT", NAME_FLAG_ATTACH_GLOBAL);
	printf("Mock Mqtt started\n");

	rcid_m_hal = name_open(GNS_NAME, NAME_FLAG_ATTACH_GLOBAL);
	if (-1 == rcid_m_hal){
			perror("hal: name_open on Dispatcher failed");
			return -1;
	}
	printf("Mock Hal connected\n");

	rcid_m_fsm = name_open(GNS_NAME, NAME_FLAG_ATTACH_GLOBAL);
		if (-1 == rcid_m_fsm){
				perror("fsm: name_open on Dispatcher failed");
				return -1;
	}
	printf("Mock Fsm connected\n");

	rcid_m_qnet = name_open("Dispatcher", NAME_FLAG_ATTACH_GLOBAL);
	if (-1 == rcid_m_qnet){
		perror("qnet: name_open on Dispatcher failed");
		return -1;
	}
	printf("Mock Qnet connected\n");

	rcid_m_mqtt = name_open("Dispatcher", NAME_FLAG_ATTACH_GLOBAL);
	if (-1 == rcid_m_mqtt){
		perror("mqtt: name_open on Dispatcher failed");
		return -1;
	}
	printf("Mock Mqtt connected\n");

	MsgSendPulse(rcid_m_hal, SIGEV_PULSE_PRIO_INHERIT, HAL_READY, 0);
	printf("send HAL_READY\n");
	int rcvid = MsgReceive (m_hal->chid, &header, sizeof (header_t), NULL);
	MsgReply( rcvid, EOK, NULL, 0 );
	sleep(2);
	MsgSendPulse(rcid_m_fsm, SIGEV_PULSE_PRIO_INHERIT, FSM_READY, 0);
	printf("send FSM_READY\n");
	rcvid = MsgReceive (m_fsm->chid, &header, sizeof (header_t), NULL);
	MsgReply( rcvid, EOK, NULL, 0 );
	sleep(2);
	MsgSendPulse(rcid_m_qnet, SIGEV_PULSE_PRIO_INHERIT, QNET_READY, 0);
	printf("send QNET_READY\n");
	rcvid = MsgReceive (m_qnet->chid, &header, sizeof (header_t), NULL);
	MsgReply( rcvid, EOK, NULL, 0 );
	sleep(2);
	MsgSendPulse(rcid_m_mqtt, SIGEV_PULSE_PRIO_INHERIT, MQTT_READY, 0);
	printf("send MQTT_READY\n");
	rcvid = MsgReceive (m_mqtt->chid, &header, sizeof (header_t), NULL);
	MsgReply( rcvid, EOK, NULL, 0 );
	sleep(2);

	MsgSendPulse(rcid_m_mqtt, SIGEV_PULSE_PRIO_INHERIT, TESTEVENT, 0);
	printf("send TESTEVENT\n");

	do{
	if (rcvid == -1) { // Error occurred
		perror("Server: MsgReceived failed");
	}
	if(header.code == TESTEVENT){
		printf("Dispatcher works\n");
	}
	else{
		printf("Another Message was recieved\n");
	}
	}while(header.code != TESTEVENT);
	printf("Test Ende\n");
}
