#ifndef SENDER_H
#define SENDER_H
#pragma once

#include "Throw.h"

#include <sys/dispatch.h>
#include <string>
#include <sys/neutrino.h>
#include <stdint.h>
namespace QNet{
	class Sender {
	public: //============================================ contructors & destructors ============================================
		Sender(const std::string receiver_name);
		virtual ~Sender();


	public: //================================================ public functions ================================================
		void send(int8_t code, int value, int priority = SIGEV_PULSE_PRIO_INHERIT);
		int getConnectionID();



	private: //================================================ private variables ================================================
		int connectionID;



	private: //================================================ private functions ================================================
		//void privateFunction();

	};

}
#endif