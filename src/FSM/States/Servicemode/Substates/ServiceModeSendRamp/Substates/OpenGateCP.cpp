#include "OpenGateCP.h"

//================================================= contructors & destructors =================================================
OpenGateCP::OpenGateCP(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

OpenGateCP::~OpenGateCP() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void OpenGateCP::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->timer->start_timer(250, TIMER_ID::OPEN_GATE_CP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
}

void OpenGateCP::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

I_State* OpenGateCP::timer(TIMER_ID id){
    if(id == TIMER_ID::OPEN_GATE_CP){
        return new IdleGateCP(data);
    }
    return nullptr;
}