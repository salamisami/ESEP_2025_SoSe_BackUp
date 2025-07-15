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
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_ON);
    
}

void COMReconnected::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) Error_Enum::ERROR_C_LOST_COM);

    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::COM_ERROR_RESOLVED);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* COMReconnected::button_reset_released()
{
    return new COMNoError(data);
}

State* COMReconnected::clone() {
    return new COMReconnected(data);
}
