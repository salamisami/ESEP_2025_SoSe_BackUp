#include "NodeRedFehlerUnquittiert.h"


//================================================= constructors & destructors =================================================
NodeRedFehlerUnquittiert::NodeRedFehlerUnquittiert(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

NodeRedFehlerUnquittiert::~NodeRedFehlerUnquittiert() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void NodeRedFehlerUnquittiert::entry(){
	PRINT_STATE;
    //TODO CODE
}

void NodeRedFehlerUnquittiert::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* button_reset_released()
{
    return new NodeRedFehlerQuittiert(data);
}