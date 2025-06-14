#include "OpenGateCDF.h"

//================================================= constructors & destructors =================================================
OpenGateCDF::OpenGateCDF(ContextData* data) : HState(data) {
    //substate = new SubState(data);
}

OpenGateCDF::~OpenGateCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateCDF::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->timer->start_timer(600, TIMER_ID::OPEN_GATE_CDF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
    
}

void OpenGateCDF::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* OpenGateCDF::timer(TIMER_ID id){
    if(id == TIMER_ID::OPEN_GATE_CDF){
        return new IdleGateCDF(data);    
    }
    return nullptr;
}