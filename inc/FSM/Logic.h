#ifndef LOGIC_H
#define LOGIC_H
#pragma once

#include "QNet.h"
#include "Context.h"
#include "Idle.h"
#include "ModeHandler.h"
#include "Event.h"

#ifdef MOCK
#include "Mock_PM.h"
#else
#include "PulseMsg.h"
#endif

#include <thread>

class Logic {
public: //============================================ contructors & destructors ============================================
	Logic(Mock_PM::Receiver* local_receiver, Mock_PM::Sender* local_sender, I_Sender* timer_sender);
    Logic(I_Receiver* local_receiver, I_Sender* local_sender);
	//Logic(I_Receiver* local_receiver, I_Sender* local_sender, I_Sender* timer_sender);
    virtual ~Logic();
	

public: //================================================ public functions ================================================
	//void publicFunction();
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread logicThread;
	//pointers
	I_Receiver* local_receiver;
	I_Sender* local_sender;
	I_Sender* timer_sender;
	//primitive types
	//bool and char
	bool logicRunning;
   
	

private: //================================================ private functions ================================================
	void threadFunction();
	
};

#endif