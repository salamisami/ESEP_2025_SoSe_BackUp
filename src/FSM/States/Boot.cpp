#include "Boot.h"

//================================================= constructors & destructors =================================================
Boot::Boot(ContextData* data): State(data) {}

Boot::~Boot() {}

//===================================================== private functions =====================================================

//void Boot::privateFunction(){}

//===================================================== public functions =====================================================

void Boot::entry(){
    PRINT_STATE;
}

void Boot::exit(){
    PRINT_STATE;
}

State* Boot::is_pusher(){
    data->is_switch = false;
    return new ModeHandler(data);
}

State* Boot::is_switch(){
    data->is_switch = true;
    return new ModeHandler(data);
}