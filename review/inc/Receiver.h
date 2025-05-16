#ifndef RECEIVER_H
#define RECEIVER_H
#pragma once

#include "Throw.h"

#include <string>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
namespace QNet{
	class Receiver {
	public: //============================================ contructors & destructors ============================================
		
		Receiver(const std::string name);
		virtual ~Receiver();


	public: //================================================ public functions ================================================
		_pulse receive();



	private: //================================================ private variables ================================================
		name_attach_t* attach;




	private: //================================================ private functions ================================================
		//void privateFunction();

	};

}
#endif