#include "EStopReleased.h"

//================================================= constructors & destructors =================================================
EStopReleased::EStopReleased(ContextData* data) : State(data) {}

EStopReleased::~EStopReleased() {}

//===================================================== private functions =====================================================

//void EStopReleased::privateFunction(){}

//===================================================== public functions =====================================================

void EStopReleased::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON);
}

void EStopReleased::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* EStopReleased::button_reset_pressed(){
    return new EStopQuit(data);
}

I_State* EStopReleased::button_estop_pressed(){
    return new EStopViaLocal(data);
}

I_State* EStopReleased::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}