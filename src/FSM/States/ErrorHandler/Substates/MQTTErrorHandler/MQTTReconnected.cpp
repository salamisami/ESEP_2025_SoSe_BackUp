#include "MQTTReconnected.h"



//================================================= constructors & destructors =================================================
MQTTReconnected::MQTTReconnected(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTReconnected::~MQTTReconnected() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTReconnected::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTReconnected::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MQTTReconnected::button_reset_released()
{
    return new MQTTNoError(data);
}