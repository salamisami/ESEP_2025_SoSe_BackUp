#include "RampErrorQuittiert.h"


RampErrorQuittiert::RampErrorQuittiert(ContextData* data) : State(data) 
{}

RampErrorQuittiert::~RampErrorQuittiert() {
    
}

void RampErrorQuittiert::entry() {
    PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::TRAFFIC_RED_ON);
}

void RampErrorQuittiert::exit() {
    //TODO CODE
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
