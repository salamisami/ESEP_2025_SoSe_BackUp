#include "MQTTFehlerQuittiert.h"
#include "MQTTFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
MQTTFehlerUnquittiert::MQTTFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTFehlerUnquittiert::~MQTTFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new MQTTFehlerUnquittiert(data);
}