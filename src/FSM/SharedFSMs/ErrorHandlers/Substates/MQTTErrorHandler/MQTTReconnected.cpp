#include "MQTTReconnected.h"



//================================================= constructors & destructors =================================================
MQTTReconnected::MQTTReconnected(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTReconnected::~MQTTReconnected() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTReconnected::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTReconnected::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::MOTOR_SLOW, data->event_payload);    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::MQTT_ERROR_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* MQTTReconnected::button_reset_released()
{
    return new MQTTNoError(data);
}