#ifndef EVENTPRIORITY_H
#define EVENTPRIORITY_H
#pragma once


#ifdef MOCK
#define SIGEV_PULSE_PRIO_INHERIT -1
#else
#include <sys/neutrino.h>
#endif


enum class EventPriority : int{
	DEFAULT = SIGEV_PULSE_PRIO_INHERIT,
	THIRD_PRIO = 253,
	SECOND_PRIO,
	FIRST_PRIO
};

#endif