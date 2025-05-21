#ifndef TIMER_H
#define TIMER_H
#pragma once

#include "EventPriority.h"
#include "Event.h"
#include "Macros.h"
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <thread>


class Timer {
public: //============================================ contructors & destructors ============================================
	/**
	 * @brief Creates a timer linked to a connection ID, on which the timer events are sent
	 * @param feedbackConnectionID the connection ID, for the events to be sent to
	 */
	Timer(int feedbackConnectionID);
	virtual ~Timer();


public: //================================================ public functions ================================================

	/**
	 * @brief set a timer, and send the alarm to @param feedbackConnectionID
	 *
	 * @param miliseconds how long should the timer be set
	 * @param id timer ID, which will be saved to the event.value
	 */
	void setTimer(int miliseconds, int id);



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread timerThread;
	//pointers
	//primitive types
	int coid;
	//bool and char



private: //================================================ private functions ================================================
	void threadFunction(int miliseconds, int id);

};

#endif