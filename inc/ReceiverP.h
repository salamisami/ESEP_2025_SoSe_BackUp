#ifndef RECEIVERP_H
#define RECEIVERP_H
#pragma once

#include "Throw.h"

#include <string>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
namespace PM{
	class Receiver {
	public: //============================================ contructors & destructors ============================================
		
		Receiver();
		virtual ~Receiver();


	public: //================================================ public functions ================================================
		_pulse receive();
		int getChannelID();



	private: //================================================ private variables ================================================
		int channelID;




	private: //================================================ private functions ================================================
		//void privateFunction();

	};

}
#endif