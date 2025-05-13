/*
 * QnetDisconnected.h
 *
 *  Created on: 07.05.2025
 *      Author: User
 */

#ifndef STATES_QNETDISCONNECTED_H_
#define STATES_QNETDISCONNECTED_H_

#include "FsmConnected.h"
#include "FsmDisconnected.h"
#include "HalConnected.h"
#include "HalDisconnected.h"
#include "MqttConnected.h"
#include "MqttDisconnected.h"
#include "QnetConnected.h"
#include "DispatcherOnline.h"
#include "NoConnections.h"

class QnetDisconnected: public BaseState {
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

#endif /* STATES_QNETDISCONNECTED_H_ */
