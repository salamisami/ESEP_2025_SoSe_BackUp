#include "COMReconnectedUnquittiert.h"



//================================================= constructors & destructors =================================================
COMReconnectedUnquittiert::COMReconnectedUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMReconnectedUnquittiert::~COMReconnectedUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMReconnectedUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
}

void COMReconnectedUnquittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::MOTOR_SLOW, data->event_payload);    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::COM_ERROR_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* COMReconnectedUnquittiert::button_reset_released()
{
    return new COMNoError(data);
}

State* COMReconnectedUnquittiert::clone() {
    return new COMReconnectedUnquittiert(data);
}