#include "ADCFrei.h"


//================================================= constructors & destructors =================================================
ADCFrei::ADCFrei(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ADCFrei::~ADCFrei() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCFrei::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ADCFrei::exit(){
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t)Topic::MOTOR_SLOW, data->event_payload);
    data->sender->send_event((int8_t)Topic::ERROR, (int) Error_Enum::ERROR_INVALID_MEASURE_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* ADCFrei::button_reset_released() {
    return new ValidMeasure(data);
}