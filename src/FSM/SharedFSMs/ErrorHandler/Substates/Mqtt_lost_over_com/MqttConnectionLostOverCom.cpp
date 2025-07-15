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
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_SLOW, (int)EventPriority::DEFAULT);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_GREEN_OFF, (int)EventPriority::DEFAULT);
	data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int)Error_Enum::ERROR_C_LOST_MQTT_OVER_COM, (int)EventPriority::DEFAULT);
	data->error_warning_counter->error_or_warning_occured();
}

void MqttConnectionLostOverCom::exit(){
		data->sender->send_event((int8_t) Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_OFF, (int)EventPriority::DEFAULT);
		data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int)Error_Enum::ERROR_C_LOST_MQTT_OVER_COM, (int)EventPriority::DEFAULT);
		data->error_warning_counter->error_or_warning_resolved();
}

State* MqttConnectionLostOverCom::com_mqtt_connected(){
	return new NoMqttConnectionLost(data);
}
