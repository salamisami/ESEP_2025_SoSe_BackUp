#include "IdleServiceMode.h"

//================================================= constructors & destructors =================================================
IdleServiceMode::IdleServiceMode(ContextData* data) : State(data) {
	//substate = new SubState(data);
}

IdleServiceMode::~IdleServiceMode() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleServiceMode::entry() {
	PRINT_STATE;
	DEBUG("Please put W_H");
}

void IdleServiceMode::exit() {
	PRINT_STATE;
}

State* IdleServiceMode::laser_front_blocked() {
	return new ServiceModeSendRamp(data);
}