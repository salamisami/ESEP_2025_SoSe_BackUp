#include "IdleServiceMode.h"

//================================================= constructors & destructors =================================================
IdleServiceMode::IdleServiceMode(ContextData* data) : State(data) {
	//substate = new SubState(data);
}

IdleServiceMode::~IdleServiceMode() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleServiceMode::entry() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	DEBUG("Please put W_H");
}

void IdleServiceMode::exit() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* IdleServiceMode::laser_front_blocked() {
	return new ServiceModeSendRamp(data);
}