#ifndef THREAD_COM_H
#define THREAD_COM_H
#pragma once

#include "QNet.h"
#include "Macros.h"

#include <sys/dispatch.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>


namespace Thread_COM {
	class Receiver : public I_Receiver {
	public: //============================================ contructors & destructors ============================================
		Receiver();
		/**
		 * @brief performs name_attach to create a gns server
		 * @param name gns_name
		 */
		Receiver(const char* name);
		virtual ~Receiver();


	public: //================================================ public functions ================================================
		/**
		 * @brief receives an event
		 * @param event call by reference to a received event
		 * 
		 * @return -1 error in MsgReceive();
		 * @return 0  ein Event wird zurückgegebne
		 * @return 1 eine QNX Messgae wird zurückgegeben und
		 */
		int receive_event(_pulse* event) override;
		const char* get_name();
		int getchid() override;



	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//...
		//pointers
		name_attach_t* attach;
		const char* gns_name;
		//primitive types
		//bool and char
		//...


	private: //================================================ private functions ================================================
		void handle_app_msg(_pulse* msg, int rcvid);
		void handle_QNX_IO_msg(_pulse* msg, int rcvid);
		void handle_QNX_pulse(_pulse* msg, int rcvid);

	};

	class Sender: public I_Sender{
	public: //============================================ contructors & destructors ============================================
		Sender();
		/**
		 * @brief performs name_open to a specified gns server name
		 * @param name gns name of a created gns_server
		 */
		Sender(const char* name);
		virtual ~Sender();


	public: //================================================ public functions ================================================
		/**
		 * @brief sends an event
		 * @param event_code the Topic of the event
		 * @param event_value the data of the event
		 * @param priority the priority of the event. Leave it empty for default priority
		 */
		void send_event(int8_t event_code, int event_value, int priority = (int) EventPriority::DEFAULT) override;

		/**
		 * @brief returns connection ID
		 */
		int getcoid() override;


	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//pointers
		//primitive types
		int receiver_coid;
		//bool and char



	private: //================================================ private functions ================================================
		//void privateFunction();

	};
}
#endif
