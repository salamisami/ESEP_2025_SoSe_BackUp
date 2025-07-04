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
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::MOTOR_SLOW);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error::MQTT_ERROR_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* MQTTReconnectedUnquittiert::button_reset_released()
{
    return new MQTTNoError(data);
}