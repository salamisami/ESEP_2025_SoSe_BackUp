#ifndef PULSEMSG_H
#define PULSEMSG_H
#pragma once

#include "Macros.h"
#include "QNet.h"
#include <sys/neutrino.h>


namespace PulseMsg {
	class Receiver : public I_Receiver{
	public: //============================================ contructors & destructors ============================================
		Receiver();
		virtual ~Receiver();


	public: //================================================ public functions ================================================
		int receive_event(_pulse* event) override;
		int getchid() override;

	private: //================================================ private variables ================================================
		//classes, STL containers, and structs
		//pointers
		//primitive types
		int chid;
		//bool and char

	};

	class Sender : public I_Sender{
	public: //============================================ contructors & destructors ============================================
		Sender();
		Sender(int chid);
		virtual ~Sender();


	public: //================================================ public functions ================================================
		void send_event(int8_t code, int value, int priority = (int) EventPriority::DEFAULT) override;
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