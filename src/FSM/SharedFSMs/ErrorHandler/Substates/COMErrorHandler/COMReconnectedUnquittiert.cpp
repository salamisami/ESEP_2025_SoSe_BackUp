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
    
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    printf("Communication Reconnected.\n");
}

void COMReconnectedUnquittiert::exit(){
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) Error_Enum::ERROR_C_LOST_COM);

    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::COM_ERROR_RESOLVED);
    data->error_warning_counter->error_or_warning_resolved();
    
	PRINT_STATE;
}

State* COMReconnectedUnquittiert::button_reset_released()
{
    return new COMNoError(data);
}

State* COMReconnectedUnquittiert::clone() {
    return new COMReconnectedUnquittiert(data);
}
