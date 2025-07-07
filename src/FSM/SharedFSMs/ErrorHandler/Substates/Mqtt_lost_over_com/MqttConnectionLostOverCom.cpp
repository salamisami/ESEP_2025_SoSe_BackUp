/*
 * MqttConnectionLostOverCom.cpp
 *
 *  Created on: 06.07.2025
 *      Author: User
 */

#include "MqttConnectionLostOverCom.h"



MqttConnectionLostOverCom::MqttConnectionLostOverCom(ContextData* data) : State(data){

}

MqttConnectionLostOverCom::~MqttConnectionLostOverCom(){
}

void MqttConnectionLostOverCom::entry(){
	data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int)Error_Enum::ERROR_C_LOST_MQTT_OVER_COM, (int)EventPriority::DEFAULT);
}

void MqttConnectionLostOverCom::exit(){}

State* MqttConnectionLostOverCom::com_mqtt_connected(){
	data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int)Error_Enum::ERROR_C_LOST_MQTT_OVER_COM, (int)EventPriority::DEFAULT);
	return new NoMqttConnectionLost(data);
}
