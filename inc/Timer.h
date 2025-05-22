#ifndef TIMER_H
#define TIMER_H
#pragma once

#include "EventPriority.h"
#include "Event.h"
#include "Macros.h"
#include "QNet.h"
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <thread>


class Timer {
public: //============================================ contructors & destructors ============================================
	/**
	 * @brief Creates a timer linked to a connection ID, on which the timer events are sent
	 * @param sender the timer will use this sender interface to send the timer events
	 */
	Timer(I_Sender* sender);
	virtual ~Timer();


public: //================================================ public functions ================================================

	/**
	 * @brief set a timer, and send the alarm using @param sender
	 *
	 * @param miliseconds how long should the timer be set
	 * @param id timer ID, which will be saved to the event.value
	 */
	void setTimer(int miliseconds, int id);



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread timerThread;
	//pointers
	I_Sender* sender;
	//primitive types
	int coid;
	//bool and char



private: //================================================ private functions ================================================
	void threadFunction(int miliseconds, int id);

};

#endif