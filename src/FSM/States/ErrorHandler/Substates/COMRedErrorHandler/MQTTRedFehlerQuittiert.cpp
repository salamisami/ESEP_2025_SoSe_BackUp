#include "MQTTRedFehlerQuittiert.h"
#include "MQTTNoError.h"


//================================================= constructors & destructors =================================================
MQTTRedFehlerQuittiert::MQTTRedFehlerQuittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTRedFehlerQuittiert::~MQTTRedFehlerQuittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTRedFehlerQuittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTRedFehlerQuittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new MQTTNoError(data);
}