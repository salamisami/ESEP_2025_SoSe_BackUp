#include "WaitingIM.h"

//================================================= constructors & destructors =================================================
WaitingIM::WaitingIM(ContextData* data):State(data){
    
}

WaitingIM::~WaitingIM() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void WaitingIM::entry(){
	PRINT_STATE;
    data->timer->start_timer(2000, TIMER_ID::WAITING_IM);
}

void WaitingIM::exit(){
    PRINT_STATE;
}

State* WaitingIM::button_start_released(){
    return new Operating(data);
}

State* WaitingIM::timer(TIMER_ID id){
    if(id == TIMER_ID::WAITING_IM){
        return new TimerReceivedIM(data);
    }
    return nullptr;
}
