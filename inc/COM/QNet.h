#ifndef QNET_H
#define QNET_H
#pragma once

#include "EventPriority.h"
#include <sys/dispatch.h>

class I_Receiver {
public:
	virtual ~I_Receiver() = default;
	virtual int receive_event(_pulse* event) = 0;
	virtual int getchid() = 0;
};

class I_Sender {
public:
	virtual ~I_Sender() = default;
	virtual void send_event(int8_t event_code, int event_value, int priority = (int) EventPriority::DEFAULT) = 0;
	virtual int getcoid() = 0;
};

#endif