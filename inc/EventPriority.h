#ifndef EVENTPRIORITY_H
#define EVENTPRIORITY_H
#pragma once


#ifndef _WIN32
#include <sys/neutrino.h>
#else
#define SIGEV_PULSE_PRIO_INHERIT -1
#endif


enum class EventPriority : int{
	DEFAULT = SIGEV_PULSE_PRIO_INHERIT,
	THIRD_PRIO = 253,
	SECOND_PRIO,
	FIRST_PRIO
};

#endif