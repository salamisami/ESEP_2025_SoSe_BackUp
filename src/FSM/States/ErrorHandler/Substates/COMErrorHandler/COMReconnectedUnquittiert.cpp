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
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START); //Muss auf MotorController angepasst werden
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error::COM_ERROR_RESOLVED);
    //TODO CODE
	PRINT_STATE;
}

State* COMReconnectedUnquittiert::button_reset_released()
{
    return new COMNoError(data);
}