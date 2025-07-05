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
    data->sender->send_event((int8_t)Topic::INTERNAL, (int)Internal_Enum::MOTOR_SLOW);
    data->sender->send_event((int8_t)Topic::ERROR, (int) Error::ERROR_INVALID_MEASURE_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* ADCFrei::button_reset_released() {
    return new ValidMeasure(data);
}