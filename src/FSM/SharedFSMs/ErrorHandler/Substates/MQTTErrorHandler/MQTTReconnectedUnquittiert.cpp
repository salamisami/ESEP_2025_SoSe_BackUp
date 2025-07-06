#include "MQTTReconnectedUnquittiert.h"



//================================================= constructors & destructors =================================================
MQTTReconnectedUnquittiert::MQTTReconnectedUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTReconnectedUnquittiert::~MQTTReconnectedUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTReconnectedUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
}

void MQTTReconnectedUnquittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::MOTOR_SLOW, data->event_payload);    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::MQTT_ERROR_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* MQTTReconnectedUnquittiert::button_reset_released()
{
    return new MQTTNoError(data);
}

State* MQTTReconnectedUnquittiert::clone() {
    return new MQTTReconnectedUnquittiert(data);
}