#include "Servicemode.h"

//================================================= constructors & destructors =================================================
Servicemode::Servicemode(ContextData* data)
    : HState(data) {
    substate = new IdleServiceMode(data);
}

Servicemode::~Servicemode() {}

//===================================================== private functions =====================================================

//void Servicemode::privateFunction(){}

//===================================================== public functions =====================================================

void Servicemode::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_FAST);
    HState::entry();
}

void Servicemode::exit() {
    HState::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
}

HState* Servicemode::button_stop_pressed() {
    return new Idle(data);
}