#include "RampErrorUnquittiert.h"

RampErrorUnquittiert::RampErrorUnquittiert(ContextData* data) : State(data) 
{}

RampErrorUnquittiert::~RampErrorUnquittiert() {
    
}

void RampErrorUnquittiert::entry() {
    PRINT_STATE;
    
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON_FAST);
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_BOTH_R_FULL); 
    data->error_warning_counter->error_or_warning_occured();
    printf("Error: Both Ramps full. Please empty both Ramps and then press the Reset Button.\n");
}

void RampErrorUnquittiert::exit() {
    
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

State* RampErrorUnquittiert::clone() {
    return new RampErrorUnquittiert(data);
}
