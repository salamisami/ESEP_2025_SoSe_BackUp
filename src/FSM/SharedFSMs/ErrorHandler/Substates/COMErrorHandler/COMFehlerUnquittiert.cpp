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
    
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_FAST);
    data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) Error_Enum::ERROR_C_LOST_COM);
    data->error_warning_counter->error_or_warning_occured();
    printf("Error: Communication Error with FBM. Please press Reset Button.\n");
}

void COMFehlerUnquittiert::exit(){
    
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
