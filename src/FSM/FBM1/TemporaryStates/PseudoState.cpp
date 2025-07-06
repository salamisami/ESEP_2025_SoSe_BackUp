#include "PseudoState.h"

//================================================= constructors & destructors =================================================
PseudoState::PseudoState(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PseudoState::~PseudoState() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PseudoState::entry(){
	PRINT_STATE;
}

void PseudoState::exit(){
	PRINT_STATE;
}

State* PseudoState::clone(){
	return new PseudoState(data);
}