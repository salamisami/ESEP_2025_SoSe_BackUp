#include "EStopQuit.h"

//================================================= constructors & destructors =================================================
EStopQuit::EStopQuit(ContextData* data) : HState(data) {}

EStopQuit::~EStopQuit() {}

//===================================================== private functions =====================================================

//void EStopQuit::privateFunction(){}

//===================================================== public functions =====================================================

void EStopQuit::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

void EStopQuit::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* EStopQuit::button_estop_pressed(){
    return new EStopViaLocal(data);
}

State* EStopQuit::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}

State* EStopQuit::button_reset_released(){
    return new ModeHandler(data);
}