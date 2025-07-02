#include "MQTTFehlerQuittiert.h"


//================================================= constructors & destructors =================================================
MQTTFehlerQuittiert::MQTTFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTFehlerQuittiert::~MQTTFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MQTTFehlerQuittiert::mqtt_connected()
{
    return new MQTTNoError(data);
}