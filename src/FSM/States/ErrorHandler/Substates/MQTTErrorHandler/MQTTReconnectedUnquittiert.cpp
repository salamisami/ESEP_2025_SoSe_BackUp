#include "MQTTReconnectedUnquittiert.h"



//================================================= constructors & destructors =================================================
MQTTReconnectedUnquittiert::MQTTReconnectedUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTReconnectedUnquittiert::~MQTTReconnectedUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTReconnectedUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTReconnectedUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MQTTReconnectedUnquittiert::button_reset_released()
{
    return new MQTTNoError(data);
}