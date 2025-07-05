#include "PieceLostFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
PieceLostFehlerUnquittiert::PieceLostFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceLostFehlerUnquittiert::~PieceLostFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceLostFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::MOTOR_STOP_FSM);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
}

void PieceLostFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* PieceLostFehlerUnquittiert::button_reset_released()
{
    return new PieceLostFehlerQuittiert(data);
}

State* PieceLostFehlerUnquittiert::clone() {
    return new PieceLostFehlerUnquittiert(data);
}