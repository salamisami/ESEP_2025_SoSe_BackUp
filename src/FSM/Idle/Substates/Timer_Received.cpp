#include "Timer_Received.h"

//================================================= contructors & destructors =================================================
Timer_Received::Timer_Received(ContextData* data) :State(data) {}

Timer_Received::~Timer_Received() {}

//===================================================== private functions =====================================================

//void Timer_Received::privateFunction(){}

//===================================================== public functions =====================================================

//void Timer_Received::publicFunction(){}
void Timer_Received::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void Timer_Received::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Timer_Received::button_start_released(){
    return new Servicemode(data);
}
