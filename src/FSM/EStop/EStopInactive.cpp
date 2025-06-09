#include "EStopInactive.h"

//================================================= contructors & destructors =================================================
EStopInactive::EStopInactive(ContextData* data) : State(data) {
    substate = new EStopReleased(data);
}

EStopInactive::~EStopInactive() {}

//===================================================== private functions =====================================================

//void EStopInactive::privateFunction(){}

//===================================================== public functions =====================================================

void EStopInactive::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    State::entry();
}

void EStopInactive::exit(){
    State::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* EStopInactive::button_estop_pressed(){
    return new EStopViaLocal(data);
}

I_State* EStopInactive::com_button_estop_pressed(){
    return new EStopViaNeigbor(data);
}

I_State* EStopInactive::button_reset_released(){
    return new ModeHandler(data);
}