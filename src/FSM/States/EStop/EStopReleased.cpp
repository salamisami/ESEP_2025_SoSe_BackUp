#include "EStopReleased.h"

//================================================= constructors & destructors =================================================
EStopReleased::EStopReleased(ContextData* data) : State(data) {}

EStopReleased::~EStopReleased() {}

//===================================================== private functions =====================================================

//void EStopReleased::privateFunction(){}

//===================================================== public functions =====================================================

void EStopReleased::entry(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON);
}

void EStopReleased::exit(){
    PRINT_STATE;
}

State* EStopReleased::button_reset_pressed(){
    return new EStopQuit(data);
}

State* EStopReleased::button_estop_pressed(){
    return new EStopViaLocal(data);
}

State* EStopReleased::com_button_estop_pressed(){
    return new EStopViaNeighbor(data);
}

State* EStopReleased::clone() {
    return new EStopReleased(data);
}