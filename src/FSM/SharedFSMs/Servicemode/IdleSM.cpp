#include "IdleSM.h"

//================================================= constructors & destructors =================================================
IdleSM::IdleSM(ContextData* data) : State(data) {
	//substate = new SubState(data);
}

IdleSM::~IdleSM() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleSM::entry() {
	PRINT_STATE;
	printf("Please put Flat Piece.");
}

void IdleSM::exit() {
	PRINT_STATE;
}


State* IdleSM::laser_front_blocked() {
	return new ServiceModeSendRamp(data);
}

State* IdleSM::clone() {
	return new IdleSM(data);
}