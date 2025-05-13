/*
 * FsmConnected.h
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#ifndef STATES_FSMCONNECTED_H_
#define STATES_FSMCONNECTED_H_

#include "BaseState.h"
#include "DispatcherOnline.h"
#include "FsmDisconnected.h"
#include "HalConnected.h"
#include "HalDisconnected.h"
#include "MqttConnected.h"
#include "MqttDisconnected.h"
#include "QnetConnected.h"
#include "QnetDisconnected.h"
#include "NoConnections.h"

class FsmConnected: public BaseState {
public:
	virtual void entry() override;
	virtual void exit() override;
	virtual void fsm_ready() override;
	virtual void hal_ready() override;
	virtual void mqtt_ready() override;
	virtual void qnet_ready() override;
	virtual void fsm_not_ready() override;
	virtual void hal_not_ready() override;
	virtual void qnet_not_ready() override;
	virtual void mqtt_not_ready() override;
	virtual void dispatcher_ready() override;
	virtual void dispatch_message() override;
};

#endif /* STATES_FSMCONNECTED_H_ */
