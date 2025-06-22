#include "Green.h"

//================================================= constructors & destructors =================================================
Green::Green(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Green::~Green() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Green::entry(){
	PRINT_STATE;
}

void Green::exit(){
	PRINT_STATE;
}

State* Green::button_start_pressed(){
	return new Yellow(data);
}