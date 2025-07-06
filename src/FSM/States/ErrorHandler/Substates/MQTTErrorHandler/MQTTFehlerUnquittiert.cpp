#include "MQTTFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
MQTTFehlerUnquittiert::MQTTFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTFehlerUnquittiert::~MQTTFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_C_LOST_COM);
}

void MQTTFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MQTTFehlerUnquittiert::button_reset_released()
{
    return new MQTTFehlerQuittiert(data);
}

State* MQTTFehlerUnquittiert::mqtt_connected()
{
    return new MQTTReconnectedUnquittiert(data);
}