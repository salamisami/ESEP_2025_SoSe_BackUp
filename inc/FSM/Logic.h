#ifndef LOGIC_H
#define LOGIC_H
#pragma once

#include "QNet.h"
#include "Context.h"
#include "Idle.h"
#include "Boot.h"
#include "Event.h"
#include "Thread_COM.h"

#include "Mock_PM.h"

#include <thread>

class Logic {
public: //============================================ constructors & destructors ============================================
	/**
	 * @brief This constructor is used, if the dispatcher is smart, so that the logic will use 2 different senders to send events out and send event to itself.
	 * @param local sender to send events out
	 * @param to_self_sender to send events to self. If this parameter is not specified, The context will use the same sender to send events out and to self. Use this if the dispatcher is broadcast type
	 */
	Logic(I_Receiver* local_receiver, I_Sender* local_sender, I_Sender* to_self_sender = nullptr);
	virtual ~Logic();


public: //================================================ public functions ================================================
	std::string show_state();



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread logicThread;
	//pointers
	I_Receiver* local_receiver;
	I_Sender* local_sender;
	I_Sender* to_self_sender;
	ContextData* data;
	Context<Boot>* fsm;
	//primitive types
	//bool and char
	bool logicRunning;



private: //================================================ private functions ================================================
	void threadFunction();

};

#endif