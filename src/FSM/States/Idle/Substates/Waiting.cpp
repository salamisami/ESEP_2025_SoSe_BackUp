#include "Waiting.h"

//================================================= contructors & destructors =================================================
Waiting::Waiting(ContextData* data):State(data){
    
}

Waiting::~Waiting() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Waiting::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->timer->setTimer(2000, IDLE_TIMER);
}

void Waiting::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* Waiting::button_start_released(){
    return new Operating(data);
}

I_State* Waiting::timer(int id){
    if(id == IDLE_TIMER){
        return new Timer_Received(data);
    }
    return nullptr;
}