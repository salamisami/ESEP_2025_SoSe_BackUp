#include "MQTTNoError.h"


//================================================= constructors & destructors =================================================
MQTTNoError::MQTTNoError(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

MQTTNoError::~MQTTNoError() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MQTTNoError::entry(){
	PRINT_STATE;
    //TODO CODE
}

void MQTTNoError::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* MQTTNoError::error_c_lost_mqtt()
{
    return new MQTTFehlerUnquittiert(data);
}

State* MQTTNoError::clone() {
    return new MQTTNoError(data);
}