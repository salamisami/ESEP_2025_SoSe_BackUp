/*
 * Dispatcher.h
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Action.h"
#include "Data.h"
#include "Context.h"

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	int start_dispatcher();
	typedef struct _pulse header_t;


private:
	Action *action;
	Data *data;
	Context *context;

	int handle_app_msg(header_t header,int rcvid);
	int handle_pulse_msg(header_t header, int rcvid);
	int handle_QNX_IO_msg(header_t header,int rcvid);
	int handle_QNX_pulse(header_t header,int rcvid);
	int handle_appl_pulse(header_t header,int rcvid);
};



#endif /* DISPATCHER_H_ */
