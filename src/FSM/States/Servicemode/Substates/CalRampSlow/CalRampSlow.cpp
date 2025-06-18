#include "CalRampSlow.h"


//================================================= constructors & destructors =================================================
CalRampSlow::CalRampSlow(ContextData* data) : OrthState(data, std::vector<State*>(
    {
        new EndToGateCRS(data),
        new PusherIdleCRS(data)
    }
)) {
    //substate = new SubState(data);
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

State* CalRampSlow::laser_ramp_blocked() {
    //explicit exit
    for(auto& current_substate : substates) {
        State* newSubstate = current_substate->laser_ramp_blocked();
        if(newSubstate != nullptr) {
            return newSubstate;
        }
    }
    return nullptr;
}