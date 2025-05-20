/*
 * Dispatcher.h
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Ithreadcom.h"

#define MAX_NUM_COMP 5

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	void run_dispatcher();
	typedef struct _pulse header_t;


private:
	Ithread_com *threadcom;

	int coid_arr[MAX_NUM_COMP] = {0,0,0,0,0};

	int handle_appl_pulse(header_t header,int rcvid);
};



#endif /* DISPATCHER_H_ */
