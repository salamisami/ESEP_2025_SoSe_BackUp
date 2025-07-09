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
    
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_W_APPEARED); 
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
}

void PieceAppearedFehlerUnquittiert::exit(){
    
	PRINT_STATE;
}

State* PieceAppearedFehlerUnquittiert::button_reset_released()
{
    return new PieceAppearedFehlerQuittiert(data);
}

State* PieceAppearedFehlerUnquittiert::clone() {
    return new PieceAppearedFehlerUnquittiert(data);
}