#include "Red.h"

//================================================= constructors & destructors =================================================
Red::Red(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Red::~Red() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Red::entry(){
	PRINT_STATE;
}

void Red::exit(){
	PRINT_STATE;
}

State* Red::button_start_pressed(){
	return new Green(data);
}