#include "Waiting.h"

//================================================= constructors & destructors =================================================
Waiting::Waiting(ContextData* data):State(data){
    
}

Waiting::~Waiting() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Waiting::entry(){
	PRINT_STATE;
    data->timer->start_timer(2000, TIMER_ID::WAITING_BUTTON_START);
}

void Waiting::exit(){
    PRINT_STATE;
}

State* Waiting::button_start_released(){
    return new Operating(data);
}

State* Waiting::timer(TIMER_ID id){
    if(id == TIMER_ID::WAITING_BUTTON_START){
        return new Timer_Received(data);
    }
    return nullptr;
}
