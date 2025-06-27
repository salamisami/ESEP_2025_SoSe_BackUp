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
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);

}

//load history
State* WaitingIM::button_start_released() {
    if(data->stateStack->empty()) {
        return new OperatingMock(data);
    }
    State* loaded_state = data->stateStack->top();
    data->stateStack->pop();
    // while(!data->stateStack->empty()) {
    //     delete data->stateStack->top();
    //     data->stateStack->pop();
    // }
    return loaded_state;
}

State* WaitingIM::timer(TIMER_ID id) {
    if(id == TIMER_ID::WAITING_IM) {
        return new TimerReceivedIM(data);
    }
    return nullptr;
}
