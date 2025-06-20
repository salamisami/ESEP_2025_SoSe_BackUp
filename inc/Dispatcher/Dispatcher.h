/*
 * Dispatcher.h
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Thread_COM.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_NUM_COMP 2

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	void run_dispatcher();
	typedef struct _pulse header_t;


private:
	Thread_COM::Receiver *threadcom;

	int coid_arr[MAX_NUM_COMP] = {0,0};

};



#endif /* DISPATCHER_H_ */
