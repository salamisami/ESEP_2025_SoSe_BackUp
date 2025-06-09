#include "EStopQuit.h"

//================================================= contructors & destructors =================================================
EStopQuit::EStopQuit(ContextData* data) : State(data) {}

EStopQuit::~EStopQuit() {}

//===================================================== private functions =====================================================

//void EStopQuit::privateFunction(){}

//===================================================== public functions =====================================================

void EStopQuit::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_FAST);
}

void EStopQuit::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}