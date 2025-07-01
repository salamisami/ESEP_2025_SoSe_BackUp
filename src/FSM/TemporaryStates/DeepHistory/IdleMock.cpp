#include "IdleMock.h"

//================================================= constructors & destructors =================================================
IdleMock::IdleMock(ContextData* data) : State(data) {
	//substate = new SubState(data);
}

IdleMock::~IdleMock() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleMock::entry() {
	PRINT_STATE;
}

void IdleMock::exit() {
	PRINT_STATE;
}

State* IdleMock::clone() {
	return new IdleMock(data);
}

//load history if available
State* IdleMock::button_start_pressed() {
	if(data->stateStack->empty()) {
		return new OperatingMock(data);
	}
	State* loaded_history = data->stateStack->top();
	data->stateStack->pop();
	return loaded_history;
}