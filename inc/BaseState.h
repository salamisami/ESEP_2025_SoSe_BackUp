/*
 * BaseState.h
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#ifndef DISPATCHER_BASESTATE_H_
#define DISPATCHER_BASESTATE_H_

#include "Action.h"
#include "Data.h"
#include <new>

class BaseState{
public:
	Action *action;
	Data *data;

	virtual ~BaseState() = default;
	void set_action(Action *action){this->action = action;};
	void set_data(Data *data){this->data = data;};

	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void fsm_ready() = 0;
	virtual void hal_ready() = 0;
	virtual void mqtt_ready() = 0;
	virtual void qnet_ready() = 0;
	virtual void fsm_not_ready() = 0;
	virtual void hal_not_ready() = 0;
	virtual void qnet_not_ready() = 0;
	virtual void mqtt_not_ready() = 0;
	virtual void dispatcher_ready() = 0;
	virtual void dispatch_message() = 0;
};



#endif /* BASESTATE_H_ */
