#include "ADCFreiUnquittiert.h"


//================================================= constructors & destructors =================================================
ADCFreiUnquittiert::ADCFreiUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ADCFreiUnquittiert::~ADCFreiUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCFreiUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void ADCFreiUnquittiert::exit(){
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t)Topic::INTERNAL, (int)Internal_Enum::MOTOR_SLOW);
    data->sender->send_event((int8_t)Topic::ERROR, (int) Error_Enum::ERROR_INVALID_MEASURE_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* ADCFreiUnquittiert::button_reset_released() {
    return new ValidMeasure(data);
}

State* ADCFreiUnquittiert::clone() {
    return new ADCFreiUnquittiert(data);
}