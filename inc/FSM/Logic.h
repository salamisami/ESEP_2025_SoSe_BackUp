#ifndef LOGIC_H
#define LOGIC_H
#pragma once

#include "QNet.h"
#include "Context.h"
#include "Idle.h"
#include "Boot.h"
#include "Event.h"

#include "Mock_PM.h"

#include <thread>

class Logic {
public: //============================================ constructors & destructors ============================================
	/**
	 * @brief This constructor is used, if the dispatcher is smart, so that the logic will use 2 different senders to send events out and send event to itself.
	 * @param local sender to send events out
	 * @param to_self_sender to send events to self
	 */
	Logic(I_Receiver* local_receiver, I_Sender* local_sender, I_Sender* to_self_sender);
	/**
	* @brief This constructor is used, if the dispatcher is broadcast type. The context will use the same sender to send events out and to self
	* @param sender to send events out AND to self
	*/
	Logic(I_Receiver* local_receiver, I_Sender* local_sender);
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