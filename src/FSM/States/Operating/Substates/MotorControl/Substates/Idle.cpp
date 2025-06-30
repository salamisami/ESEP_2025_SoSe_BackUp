#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Idle::~Idle() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Idle::entry(){
	PRINT_STATE;
}

void Idle::exit(){
    PRINT_STATE;
}

State* Idle::motor_fast(){
    return new Fast(data);
    // TODO: Send Motor_right_start
}