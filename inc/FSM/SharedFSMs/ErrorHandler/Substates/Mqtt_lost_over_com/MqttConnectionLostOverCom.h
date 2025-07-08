/*
 * MqttConnectionLostOverCom.h
 *
 *  Created on: 06.07.2025
 *      Author: User
 */

#ifndef INC_FSM_SHAREDFSMS_ERRORHANDLER_SUBSTATES_MQTT_LOST_OVER_COM_MQTTCONNECTIONLOSTOVERCOM_H_
#define INC_FSM_SHAREDFSMS_ERRORHANDLER_SUBSTATES_MQTT_LOST_OVER_COM_MQTTCONNECTIONLOSTOVERCOM_H_


#include "State.h"
#include "ContextData.h"
#include "Event.h"
#include "NoMqttConnectionLost.h"

class MqttConnectionLostOverCom : public State{
public:
	MqttConnectionLostOverCom(ContextData* data);
	virtual ~MqttConnectionLostOverCom();

	void entry() override;
	void exit() override;
	State* clone() override {return nullptr;};
	State* com_mqtt_connected() override;
};


#endif /* INC_FSM_SHAREDFSMS_ERRORHANDLER_SUBSTATES_MQTT_LOST_OVER_COM_MQTTCONNECTIONLOSTOVERCOM_H_ */
