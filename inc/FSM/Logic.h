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
public: //============================================ contructors & destructors ============================================
	//for testing
    Logic(I_Receiver* local_receiver, I_Sender* local_sender, I_Sender* loopback_sender);
	//for real usage
	Logic(I_Receiver* local_receiver, I_Sender* local_sender);
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