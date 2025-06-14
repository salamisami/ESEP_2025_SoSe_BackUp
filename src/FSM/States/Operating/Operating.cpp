#include "Operating.h"

//================================================= constructors & destructors =================================================

Operating::Operating(ContextData* data): State(data) {
}

Operating::~Operating() {
}

//===================================================== private functions =====================================================

//void Operating::privateFunction(){}

//===================================================== public functions =====================================================

void Operating::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
}

void Operating::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Operating::button_stop_pressed() {
    return new Idle(data);
}