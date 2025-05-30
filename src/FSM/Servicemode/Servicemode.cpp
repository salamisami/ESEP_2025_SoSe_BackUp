#include "Servicemode.h"

//================================================= contructors & destructors =================================================
Servicemode::Servicemode(ContextData* data, State* previousState)
    : State(data) {

}

Servicemode::~Servicemode() {}

//===================================================== private functions =====================================================

//void Servicemode::privateFunction(){}

//===================================================== public functions =====================================================

void Servicemode::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_FAST);
}

void Servicemode::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Servicemode::button_stop_pressed(){
    return new Idle(data);
}