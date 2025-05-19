#ifndef EVENTPRIORITY_H
#define EVENTPRIORITY_H
#pragma once

#include <sched.h>
#include <sys/neutrino.h>


enum class EventPriority : int{
	DEFAULT = SIGEV_PULSE_PRIO_INHERIT,
	THIRD_PRIO = 253,
	SECOND_PRIO,
	FIRST_PRIO
};

#endif