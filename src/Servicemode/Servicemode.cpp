#include "Servicemode.h"

//================================================= contructors & destructors =================================================
Servicemode:Servicemode(ContextData* data, State* previousState)
    : State(data) {
    if(previousState == nullptr) {
        subState = new StateA(data);
    } else {
        subState = previousState;
    }
}

Servicemode::~Servicemode() {}

//===================================================== private functions =====================================================

//void Servicemode::privateFunction(){}

//===================================================== public functions =====================================================

void Servicemode::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    subState->entry();
}

void Servicemode::exit() {
    subState->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Servicemode::button_stop_pressed(){
    return new Idle(data);
}