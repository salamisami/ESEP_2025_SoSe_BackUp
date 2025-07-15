#include "CalRampSlow.h"


//================================================= constructors & destructors =================================================
CalRampSlow::CalRampSlow(ContextData* data) : OrthState(data,
    { new EndToGateCRS(data), new PusherIdleCRS(data) } ///substates
    , new CalibrationFinished(data)                  //default class
    , true
) {
    //substate = new SubState(data);
}

CalRampSlow::CalRampSlow(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, new CalibrationFinished(data), true) {
}

CalRampSlow::~CalRampSlow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalRampSlow::entry() {
    PRINT_STATE;
    OrthState::entry();
}

void CalRampSlow::exit() {
    OrthState::exit();
    PRINT_STATE;
}

State* CalRampSlow::clone() {
	return new CalRampSlow(data, OrthState::clone_substates());
}
