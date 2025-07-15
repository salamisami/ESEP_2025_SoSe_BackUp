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
    
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
}

void MQTTReconnectedUnquittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) Error_Enum::ERROR_C_LOST_MQTT);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::MQTT_ERROR_RESOLVED);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* MQTTReconnectedUnquittiert::button_reset_released()
{
    return new MQTTNoError(data);
}

State* MQTTReconnectedUnquittiert::clone() {
    return new MQTTReconnectedUnquittiert(data);
}
