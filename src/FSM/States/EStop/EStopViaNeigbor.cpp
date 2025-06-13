#include "EStopViaNeigbor.h"

//================================================= contructors & destructors =================================================
EStopViaNeighbor::EStopViaNeighbor(ContextData* data) : State(data) {}

EStopViaNeighbor::~EStopViaNeighbor() {}

//===================================================== private functions =====================================================

//void EStopViaNeigbor::privateFunction(){}

//===================================================== public functions =====================================================

void EStopViaNeighbor::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void EStopViaNeighbor::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

I_State* EStopViaNeighbor::button_estop_pressed(){
    return new BothEstopPressed(data);
}

I_State* EStopViaNeighbor::com_button_estop_released(){
    return new EStopReleased(data);
}