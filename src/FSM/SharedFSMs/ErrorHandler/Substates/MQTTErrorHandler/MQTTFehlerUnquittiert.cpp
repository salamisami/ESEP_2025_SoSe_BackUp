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
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_SLOW);
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_C_LOST_MQTT);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
    data->error_warning_counter->error_or_warning_occured();
    printf("Error: MQTT Connection Error.");
}

void MQTTFehlerUnquittiert::exit(){
	PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
}

State* MQTTFehlerUnquittiert::button_reset_released()
{
    return new MQTTFehlerQuittiert(data);
}

State* MQTTFehlerUnquittiert::mqtt_connected()
{
    return new MQTTReconnectedUnquittiert(data);
}

State* MQTTFehlerUnquittiert::clone() {
    return new MQTTFehlerUnquittiert(data);
}
