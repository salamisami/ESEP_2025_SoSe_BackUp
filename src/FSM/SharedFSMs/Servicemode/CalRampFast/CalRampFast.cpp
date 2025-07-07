#include "CalRampFast.h"


//================================================= constructors & destructors =================================================
CalRampFast::CalRampFast(ContextData* data) : OrthState(data,
    {
        new EndToGateCRF(data),
        new PusherIdleCRF(data)
    }
    , new ReadyForCDS(data)
    , true
) {
    //substate = new SubState(data);
}

CalRampFast::~CalRampFast() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalRampFast::entry() {
    PRINT_STATE;
    OrthState::entry();
}

void CalRampFast::exit() {
    OrthState::exit();
    PRINT_STATE;
}



// State* CalRampFast::laser_ramp_blocked() {
//     //explicit exit
//     for(auto& current_substate : substates) {
//         State* newSubstate = current_substate->laser_ramp_blocked();
//         if(newSubstate != nullptr) {
//             return newSubstate;
//         }
//     }
//     return nullptr;
// }