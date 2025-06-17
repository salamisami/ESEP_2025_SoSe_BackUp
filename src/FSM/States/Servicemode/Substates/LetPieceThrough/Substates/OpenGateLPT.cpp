#include "OpenGateLPT.h"

//================================================= constructors & destructors =================================================
OpenGateLPT::OpenGateLPT(ContextData* data, int duration) : State(data), duration(duration) {
    //substate = new SubState(data);
}

OpenGateLPT::~OpenGateLPT() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateLPT::entry(){
	PRINT_STATE;
    data->timer->start_timer(600, TIMER_ID::OPENGATELPT);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
    
}

void OpenGateLPT::exit(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* OpenGateLPT::timer(TIMER_ID id){
    if(id == TIMER_ID::OPENGATELPT){
        return new IdleLPT(data, duration);    
    }
    return nullptr;
}