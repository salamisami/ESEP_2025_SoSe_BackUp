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
    DEBUG("Traffic Green on Fast()");
}

void Servicemode::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Servicemode::button_stop_pressed(){
    return new Idle(data);
}