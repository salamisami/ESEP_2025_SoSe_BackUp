#include "PieceAppearedFehlerUnquittiert.h"

//================================================= constructors & destructors =================================================
PieceAppearedFehlerUnquittiert::PieceAppearedFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAppearedFehlerUnquittiert::~PieceAppearedFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAppearedFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
}

void PieceAppearedFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* PieceAppearedFehlerUnquittiert::button_reset_released()
{
    return new PieceAppearedFehlerQuittiert(data);
}