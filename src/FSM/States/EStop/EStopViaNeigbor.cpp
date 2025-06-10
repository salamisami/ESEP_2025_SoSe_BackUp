#include "EStopViaNeigbor.h"

//================================================= contructors & destructors =================================================
EStopViaNeigbor::EStopViaNeigbor(ContextData* data) : State(data) {}

EStopViaNeigbor::~EStopViaNeigbor() {}

//===================================================== private functions =====================================================

//void EStopViaNeigbor::privateFunction(){}

//===================================================== public functions =====================================================

void EStopViaNeigbor::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW);
}

void EStopViaNeigbor::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

I_State* EStopViaNeigbor::button_estop_pressed(){
    return new BothEstopPressed(data);
}

I_State* EStopViaNeigbor::com_button_estop_released(){
    return new EStopInactive(data);
}