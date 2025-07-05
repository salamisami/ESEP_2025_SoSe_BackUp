#include "PieceLostFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
PieceLostFehlerQuittiert::PieceLostFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceLostFehlerQuittiert::~PieceLostFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceLostFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
}

void PieceLostFehlerQuittiert::exit(){
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::MOTOR_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::PIECE_LOST_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* PieceLostFehlerQuittiert::button_reset_released()
{
    return new PieceLostNoError(data);
}

State* PieceLostFehlerQuittiert::clone() {
    return new PieceLostFehlerQuittiert(data);
}