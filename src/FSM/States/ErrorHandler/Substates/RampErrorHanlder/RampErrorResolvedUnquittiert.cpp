#include "RampErrorResolvedUnquittiert.h"

RampErrorResolvedUnquittiert::RampErrorResolvedUnquittiert(ContextData* data) : State(data) 
{}

RampErrorResolvedUnquittiert::~RampErrorResolvedUnquittiert() {
    
}

void RampErrorResolvedUnquittiert::entry() {
    PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_SLOW);
}

void RampErrorResolvedUnquittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error::RAMP_ERROR_RESOLVED);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START); //Muss auf MotorController angepasst werden
    //TODO CODE
	PRINT_STATE;
}

State* RampErrorResolvedUnquittiert::button_reset_released() {
    
}