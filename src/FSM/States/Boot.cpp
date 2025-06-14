#include "Boot.h"

//================================================= constructors & destructors =================================================
Boot::Boot(ContextData* data): HState(data) {}

Boot::~Boot() {}

//===================================================== private functions =====================================================

//void Boot::privateFunction(){}

//===================================================== public functions =====================================================

void Boot::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void Boot::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Boot::is_pusher(){
    data->is_switch = false;
    return new ModeHandler(data);
}

State* Boot::is_switch(){
    data->is_switch = true;
    return new ModeHandler(data);
}