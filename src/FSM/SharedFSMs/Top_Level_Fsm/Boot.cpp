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
    DEBUG("Machine is Pusher Type");
    return new Modehandler(data);
}

State* Boot::is_switch(){
    data->is_switch = true;
    DEBUG("Machine is Switch Type");
    return new Modehandler(data);
}
