/*
 * Context.h
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "BaseState.h"
#include "Data.h"
#include "Action.h"
#include "NoConnections.h"

class Context {
private:
	BaseState *state;
	Action *action;
	Data *data;
public:
	Context(Action *action, Data *data);
	virtual ~Context();

	void fsm_ready();
	void hal_ready();
	void mqtt_ready();
	void qnet_ready();
	void fsm_not_ready();
	void hal_not_ready();
	void qnet_not_ready();
	void mqtt_not_ready();
	void dispatcher_ready();
	void dispatch_message();

};

#endif /* CONTEXT_H_ */
