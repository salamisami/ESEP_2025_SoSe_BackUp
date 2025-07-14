#include "RampErrorResolvedUnquittiert.h"

RampErrorResolvedUnquittiert::RampErrorResolvedUnquittiert(ContextData* data) : State(data) 
{}

RampErrorResolvedUnquittiert::~RampErrorResolvedUnquittiert() {
    
}

void RampErrorResolvedUnquittiert::entry() {
    PRINT_STATE;
    
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_SLOW);
}

void RampErrorResolvedUnquittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::RAMP_ERROR_RESOLVED);
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) Error_Enum::ERROR_BOTH_R_FULL);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* RampErrorResolvedUnquittiert::button_reset_released() {
    return new RampNoError(data);
}

State* RampErrorResolvedUnquittiert::clone() {
    return new RampErrorResolvedUnquittiert(data);
}
