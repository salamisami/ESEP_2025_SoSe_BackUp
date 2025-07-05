/*
 * Remote_Controller.h
 *
 *  Created on: 10.06.2025
 *      Author: robin
 */

#ifndef INC_MQTT_REMOTE_CONTROLLER_H_
#define INC_MQTT_REMOTE_CONTROLLER_H_

#include "MQTT_Utilities.h"
#include "Thread_COM.h"
#include "Event.h"
#include "Macros.h"
#include "QNet.h"
#include "PulseMsg.h"


#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/dispatch.h>
//#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

#define HEARTBEAT_TIMEOUT_MS 3000
//typedef int MQTTClient_deliveryToken;

class Remote_Controller {

	public: //============================================ contructors & destructors ============================================

	Remote_Controller();


	Remote_Controller(I_Receiver* local_receiver, I_Sender* local_sender);
	virtual ~Remote_Controller();


	public: //================================================ public functions ================================================

		static std::atomic<bool> Main_running;

	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		std::thread RemConThreadRecive;
		std::thread RemConThreadSend;
		std::thread RemConThreadHeartBeat;

		//mock here
		PulseMsg::Receiver* mock_dispatcher_receiver;
		PulseMsg::Sender* mock_dispatcher_sender;

		I_Receiver* local_receiver;
		I_Sender* local_sender;

		//primitive types
		int RemCon_rcvid;
		int dispatcher_mock_rcvid;
		//bool and char
		bool RemCon_recive_running;
		bool RemCon_send_running;
		bool RemCon_HeartCheck_running;
		bool detached;



	private: //================================================ private functions ================================================

		void init(bool reinit);
		void threadFunctionRecive();
		void threadFunctionSend();
		void threadFunctionHeartbeat();
//		void connlost(char *cause); // Instanzfunktion
//		int internal_msgarrvd(char *topicName, int topicLen, MQTTClient_message *message); // Instanzfunktion
//		void delivered(MQTTClient_deliveryToken dt); // Instanzfunktion
		//void test_ins();

	};


#endif /* INC_MQTT_REMOTE_CONTROLLER_H_ */
