#include "CalGateRampFast.h"

#define OPEN_GATE_FAST 600

//================================================= constructors & destructors =================================================
CalGateRampFast::CalGateRampFast(ContextData* data) : OrthState(data, new std::vector<State*>(
    {
        new PieceGoingGate(data),
        new LetPieceThrough(data,OPEN_GATE_FAST)
    }
)) {
    //substate = new SubState(data);
}

CalGateRampFast::~CalGateRampFast() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalGateRampFast::entry() {
    PRINT_STATE
}

void CalGateRampFast::exit() {
    PRINT_STATE
}

State* CalGateRampFast::laser_ramp_blocked() {
    //explicit exit
    for(auto& current_substate : substates) {
        State* newSubstate = current_substate->laser_ramp_blocked();
        if(newSubstate != nullptr) {
            return newSubstate;
        }
    }
    return nullptr;
}