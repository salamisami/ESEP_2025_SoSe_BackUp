#include "Yellow.h"

//================================================= constructors & destructors =================================================
Yellow::Yellow(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Yellow::~Yellow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Yellow::entry(){
	PRINT_STATE;
}

void Yellow::exit(){
	PRINT_STATE;
}

State* Yellow::button_start_pressed(){
	return new Red(data);
}