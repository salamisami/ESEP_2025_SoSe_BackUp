/*
 * NoMqttConnectionLost.h
 *
 *  Created on: 06.07.2025
 *      Author: User
 */

#ifndef INC_FSM_SHAREDFSMS_ERRORHANDLER_SUBSTATES_MQTT_LOST_OVER_COM_NOMQTTCONNECTIONLOST_H_
#define INC_FSM_SHAREDFSMS_ERRORHANDLER_SUBSTATES_MQTT_LOST_OVER_COM_NOMQTTCONNECTIONLOST_H_


#include "State.h"
#include "ContextData.h"
#include "MqttConnectionLostOverCom.h"

class NoMqttConnectionLost : public State{
public:
	NoMqttConnectionLost(ContextData* data);
	virtual ~NoMqttConnectionLost();

	void entry() override;
	void exit() override;

	State* com_mqtt_disconnected() override;
};


#endif /* INC_FSM_SHAREDFSMS_ERRORHANDLER_SUBSTATES_MQTT_LOST_OVER_COM_NOMQTTCONNECTIONLOST_H_ */
