#ifndef THREAD_COM_H
#define THREAD_COM_H
#pragma once

#include <sys/dispatch.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

#define FBM 1

//FBM_1
#define FBM_1_HAL "Hal_1"
#define FBM_1_FSM "Fsm_1"
#define FBM_1_COM "Com_1"
#define FBM_1_RECORDER "Rec_1"
#define FBM_1_REMOTE "Rem_1"
#define FBM_1_DISPATCHER "Dis_1"
//FBM_2
#define FBM_2_HAL "Hal_2"
#define FBM_2_FSM "Fsm_2"
#define FBM_2_COM "Com_2"
#define FBM_2_RECORDER "Rec_2"
#define FBM_2_REMOTE "Rem_2"
#define FBM_2_DISPATCHER "Dis_2"

namespace Thread_COM {
	class Receiver {
	public: //============================================ contructors & destructors ============================================
		Receiver(const char* name);
		virtual ~Receiver() = default;


	public: //================================================ public functions ================================================
		int receive_event(_pulse* event);
		int get_coid();
		const char* get_name();



	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//...
		//pointers
		name_attach_t* attach;
		const char* gns_name;
		//primitive types
		int coid;
		//bool and char
		//...


	private: //================================================ private functions ================================================
		void handle_app_msg(_pulse* msg, int rcvid);
		void handle_QNX_IO_msg(_pulse* msg, int rcvid);
		void handle_QNX_pulse(_pulse* msg, int rcvid);

	};

	class Sender {
	public: //============================================ contructors & destructors ============================================
		Sender(int coid);
		virtual ~Sender() = default;


	public: //================================================ public functions ================================================
		void send_event(int8_t event_code, int event_value, int priority = SIGEV_PULSE_PRIO_INHERIT);



	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//pointers
		//primitive types
		int coid;
		//bool and char



	private: //================================================ private functions ================================================
		//void privateFunction();

	};
}
#endif