#include "TrafficMock.h"

//================================================= constructors & destructors =================================================
TrafficMock::TrafficMock(ContextData* data) : HState(data, new Green(data)) {}
TrafficMock::TrafficMock(ContextData* data, State* initial_state) : HState(data, initial_state) {}

TrafficMock::~TrafficMock() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void TrafficMock::entry() {
	PRINT_STATE;
	//action here
	HState::entry();
}

void TrafficMock::exit() {
	HState::exit();
	PRINT_STATE;
	//action here
}

State* TrafficMock::clone() {
	return new TrafficMock(data, substate->clone());
}