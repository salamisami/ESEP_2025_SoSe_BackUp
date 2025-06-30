#include "Fast.h"

//================================================= constructors & destructors =================================================
Fast::Fast(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Fast::~Fast() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Fast::entry(){
	PRINT_STATE;
}

void Fast::exit(){
    PRINT_STATE;

}

State* Fast::DELETE_W_MOTOR(){
    TODO:Choice workpieces
}