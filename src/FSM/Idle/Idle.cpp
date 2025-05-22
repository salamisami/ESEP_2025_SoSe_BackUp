#include "Idle.h"

//================================================= contructors & destructors =================================================
Idle::Idle(ContextData* data, State* previousState) : State(data) {
    if(previousState == nullptr) {
        subState = new Traffic_Green_On_Slow(data);
    } else {
        subState = previousState;
    }
}

Idle::~Idle() {
}

//===================================================== private functions =====================================================




//===================================================== public functions =====================================================

void Idle::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void Idle::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Idle::start() {
    return new Operating(data);
}

State* Idle::reset() {
    return new Idle(data);
}
