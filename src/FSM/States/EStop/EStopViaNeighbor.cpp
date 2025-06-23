#include "EStopViaNeighbor.h"

//================================================= constructors & destructors =================================================
EStopViaNeighbor::EStopViaNeighbor(ContextData* data) : State(data) {}

EStopViaNeighbor::~EStopViaNeighbor() {}

//===================================================== private functions =====================================================

//void EStopViaNeigbor::privateFunction(){}

//===================================================== public functions =====================================================

void EStopViaNeighbor::entry(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void EStopViaNeighbor::exit(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

State* EStopViaNeighbor::button_estop_pressed(){
    return new BothEstopPressed(data);
}

State* EStopViaNeighbor::com_button_estop_released(){
    return new EStopReleased(data);
}