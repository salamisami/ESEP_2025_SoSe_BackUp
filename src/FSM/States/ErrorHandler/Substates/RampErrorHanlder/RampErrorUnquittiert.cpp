#include "RampErrorUnquittiert.h"

RampErrorUnquittiert::RampErrorUnquittiert(ContextData* data) : State(data) 
{}

RampErrorUnquittiert::~RampErrorUnquittiert() {
    
}

void RampErrorUnquittiert::entry() {
    PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_FAST);
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_BOTH_R_FULL); 
}

void RampErrorUnquittiert::exit() {
    //TODO CODE
	PRINT_STATE;
}

State* RampErrorUnquittiert::ramp_not_full() {
    return new RampErrorResolvedUnquittiert(data);
}

State* RampErrorUnquittiert::com_ramp_not_full() {
    return new RampErrorResolvedUnquittiert(data);
}

State* RampErrorUnquittiert::button_reset_released() {
    return new RampErrorQuittiert(data);
}