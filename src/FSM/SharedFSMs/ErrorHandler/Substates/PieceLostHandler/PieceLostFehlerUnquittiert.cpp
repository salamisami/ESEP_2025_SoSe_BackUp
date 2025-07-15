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
    
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_W_LOST); 
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
    data->error_warning_counter->error_or_warning_occured();
}

void PieceLostFehlerUnquittiert::exit(){
    
	PRINT_STATE;
}

State* PieceLostFehlerUnquittiert::button_reset_released()
{
    return new PieceLostFehlerQuittiert(data);
}

State* PieceLostFehlerUnquittiert::clone() {
    return new PieceLostFehlerUnquittiert(data);
}
