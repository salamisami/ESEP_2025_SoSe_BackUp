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
    
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
}

void PieceLostFehlerQuittiert::exit(){
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) Error_Enum::ERROR_W_LOST);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::PIECE_LOST_RESOLVED);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* PieceLostFehlerQuittiert::button_reset_released()
{
    return new PieceLostNoError(data);
}

State* PieceLostFehlerQuittiert::clone() {
    return new PieceLostFehlerQuittiert(data);
}
