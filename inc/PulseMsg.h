#ifndef PULSEMSG_H
#define PULSEMSG_H
#pragma once

#include "Macros.h"
#include <sys/neutrino.h>


namespace PulseMsg {
	class Receiver {
	public: //============================================ contructors & destructors ============================================
		Receiver();
		virtual ~Receiver();


	public: //================================================ public functions ================================================
		_pulse receive();
		int getchid();

	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//pointers
		//primitive types
		int chid;
		//bool and char

	};

	class Sender {
	public: //============================================ contructors & destructors ============================================
		Sender();
		Sender(int chid);
		virtual ~Sender();


	public: //================================================ public functions ================================================
		void send(int8_t code, int value, int priority = SIGEV_PULSE_PRIO_INHERIT);
		int getcoid();

	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//pointers
		//primitive types
		int coid;
		//bool and char
	};

}

#endif