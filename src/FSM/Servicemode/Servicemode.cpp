#include "Servicemode.h"

//================================================= contructors & destructors =================================================
Servicemode::Servicemode(ContextData* data, State* initial_substate)
    : State(data) {
    if(initial_substate == nullptr) {
        substate = new CalibratePieces(data);
    } else {
        substate = initial_substate;
    }
}

Servicemode::~Servicemode() {}

//===================================================== private functions =====================================================

//void Servicemode::privateFunction(){}

//===================================================== public functions =====================================================

void Servicemode::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_FAST);
    substate->entry();
}

void Servicemode::exit() {
    substate->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Servicemode::button_stop_pressed(){
    return new Idle(data);
}