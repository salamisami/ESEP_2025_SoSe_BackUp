#include "Operating.h"

//================================================= contructors & destructors =================================================

Operating::Operating(ContextData* data, State* previousState)
    : State(data) {
    if(previousState == nullptr) {
        subState = new StateA(data);
    } else {
        subState = previousState;
    }
}

Operating::~Operating() {
}

//===================================================== private functions =====================================================

//void Operating::privateFunction(){}

//===================================================== public functions =====================================================

void Operating::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    subState->entry();
}

void Operating::exit() {
    subState->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Operating::reset(){
    return new Operating(data);
}

State* Operating::stop() {
    return new Idle(data);
}

State* Operating::estop() {
    data->stateStack->push(subState);
    return new EmergencyStop(data);
}

State* Operating::forward() {
    State* newSubstate = subState->forward();
    if(newSubstate != nullptr) {
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}

State* Operating::backward() {
    State* newSubstate = subState->backward();
    if(newSubstate != nullptr) {
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}

State* Operating::tick() {
    subState->exit();
    subState->entry();
    return nullptr;
}

State* Operating::service() {
    State* newSubstate = subState->service();
    if(newSubstate != nullptr) {
        return newSubstate;
    }
    return nullptr;
}