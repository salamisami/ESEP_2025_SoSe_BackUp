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
    
}

void MQTTNoError::exit(){
    
	PRINT_STATE;
}

State* MQTTNoError::error_c_lost_mqtt()
{
	DEBUG("ich bin in mqtt error gefangen");
    return new MQTTFehlerUnquittiert(data);
}

State* MQTTNoError::clone() {
    return new MQTTNoError(data);
}
