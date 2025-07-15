#include "RampErrorQuittiert.h"


RampErrorQuittiert::RampErrorQuittiert(ContextData* data) : State(data) 
{}

RampErrorQuittiert::~RampErrorQuittiert() {
    
}

void RampErrorQuittiert::entry() {
    PRINT_STATE;
    
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
}

void RampErrorQuittiert::exit() {
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
	PRINT_STATE;
}

State* RampErrorQuittiert::ramp_not_full() {
    return new RampErrorResolved(data);
}

State* RampErrorQuittiert::com_ramp_not_full() {
    return new RampErrorResolved(data);
}

State* RampErrorQuittiert::clone() {
    return new RampErrorQuittiert(data);
}
