#include "OpenGateCDS.h"

//================================================= contructors & destructors =================================================
OpenGateCDS::OpenGateCDS(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

OpenGateCDS::~OpenGateCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateCDS::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	data->timer->start_timer(1500, TIMER_ID::OPEN_GATE_CDS);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
}

void OpenGateCDS::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

I_State* OpenGateCDS::timer(TIMER_ID id){
    if(id == TIMER_ID::OPEN_GATE_CDS){
        return new IdleGateCDS(data);
    }
    return nullptr;
}