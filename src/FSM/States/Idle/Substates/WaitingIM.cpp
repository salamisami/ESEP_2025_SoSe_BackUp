#include "WaitingIM.h"

//================================================= constructors & destructors =================================================
WaitingIM::WaitingIM(ContextData* data) :State(data) {

}

WaitingIM::~WaitingIM() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void WaitingIM::entry() {
    PRINT_STATE;
    data->timer->start_timer(2000, TIMER_ID::WAITING_IM);
}

void WaitingIM::exit() {
    PRINT_STATE;
}

//load history
State* WaitingIM::button_start_released() {
    if(data->stateStack->empty()) {
        return new OperatingMock(data);
    }
    State* loaded_state = data->stateStack->top();
    data->stateStack->pop();
    return loaded_state;
}

State* WaitingIM::timer(TIMER_ID id) {
    if(id == TIMER_ID::WAITING_IM) {
        return new TimerReceivedIM(data);
    }
    return nullptr;
}

/**
HState* Operating::estop() {
    data->stateStack->push(substate);
    return new EmergencyStop(data);
}

HState* Operating::forward() {
    HState* newSubstate = substate->forward();
    if(newSubstate != nullptr) {
        HState::exit();
        delete substate;
        substate = newSubstate;
        HState::entry();
    }
    return nullptr;
}


HState* Operating::service() {
    HState* newSubstate = substate->service();
    if(newSubstate != nullptr) {
        return newSubstate;
    }
    return nullptr;
}

*/
