#include "COMReconnected.h"



//================================================= constructors & destructors =================================================
COMReconnected::COMReconnected(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMReconnected::~COMReconnected() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMReconnected::entry(){
	PRINT_STATE;
    //TODO CODE
}

void COMReconnected::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::MOTOR_SLOW);
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::COM_ERROR_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* COMReconnected::button_reset_released()
{
    return new COMNoError(data);
}