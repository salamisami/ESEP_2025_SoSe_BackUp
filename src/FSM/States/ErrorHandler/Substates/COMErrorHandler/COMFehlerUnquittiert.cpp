#include "COMFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
COMFehlerUnquittiert::COMFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMFehlerUnquittiert::~COMFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::MOTOR_STOP_FSM);
}

void COMFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* COMFehlerUnquittiert::clone() {
    return new COMFehlerUnquittiert(data);
}

State* COMFehlerUnquittiert::button_reset_released()
{
    return new COMFehlerQuittiert(data);
}

State* COMFehlerUnquittiert::com_connected()
{
    return new COMReconnectedUnquittiert(data);
}