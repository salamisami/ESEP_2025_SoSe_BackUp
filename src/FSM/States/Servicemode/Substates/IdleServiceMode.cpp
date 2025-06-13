#include "IdleServiceMode.h"

//================================================= contructors & destructors =================================================
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

I_State* IdleServiceMode::laser_front_blocked() {
	return new CalDistanceFast(data);
}

//check for explicit exit
// I_State* IdleServiceMode::laser_sorting_gate_blocked() {
// 	I_State* newSubstate = substate->laser_sorting_gate_blocked();
// 	if(newSubstate != nullptr) {
// 		return newSubstate;
// 	}
// 	return nullptr;
// }