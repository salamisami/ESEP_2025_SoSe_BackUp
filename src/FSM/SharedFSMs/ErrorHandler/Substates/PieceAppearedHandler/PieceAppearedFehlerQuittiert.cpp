#include "PieceAppearedFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
PieceAppearedFehlerQuittiert::PieceAppearedFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceAppearedFehlerQuittiert::~PieceAppearedFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceAppearedFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
}

void PieceAppearedFehlerQuittiert::exit(){
    data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) Error_Enum::ERROR_W_APPEARED);  
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::PIECE_APPEARED_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* PieceAppearedFehlerQuittiert::button_reset_released()
{
    return new PieceAppearedNoError(data);
}

State* PieceAppearedFehlerQuittiert::clone() {
    return new PieceAppearedFehlerQuittiert(data);
}