#include "Error.h"

//================================================= contructors & destructors =================================================
Error::Error(ContextData* data) : State(data){

}

Error::~Error() {}

//===================================================== private functions =====================================================

void Error::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON);
}

void Error::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
}

//===================================================== public functions =====================================================
