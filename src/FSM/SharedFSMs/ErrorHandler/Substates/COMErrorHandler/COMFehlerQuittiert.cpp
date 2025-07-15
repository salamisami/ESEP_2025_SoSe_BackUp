#include "COMFehlerQuittiert.h"



//================================================= constructors & destructors =================================================
COMFehlerQuittiert::COMFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

COMFehlerQuittiert::~COMFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void COMFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON);
    printf("Please press Reset Button\n");
}

void COMFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* COMFehlerQuittiert::clone() {
    return new COMFehlerQuittiert(data);
}

State* COMFehlerQuittiert::com_connected()
{
    return new COMReconnected(data);
}