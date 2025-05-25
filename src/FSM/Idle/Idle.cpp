#include "Idle.h"

//================================================= contructors & destructors =================================================
Idle::Idle(ContextData* data, State* previousState) : State(data) {
    if(previousState == nullptr) {
        subState = new Traffic_Green_On_Slow(data);
    } else {
        subState = previousState;
    }
}

Idle::~Idle() {
}

//===================================================== private functions =====================================================




//===================================================== public functions =====================================================

void Idle::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    subState->entry();
}

void Idle::exit() {
    subState->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Idle::button_start_pressed(){
    State* newSubstate = subState->button_start_pressed();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}
State* Idle::button_start_released(){
    State* newSubstate = subState->button_start_released();
    if(newSubstate != nullptr){
        //there is a substate change, explicit exit
        return newSubstate;
    }
    return nullptr;
}

State* Idle::timer(int id){
    State* newSubstate = subState->timer(id);
    if(newSubstate != nullptr) {
        subState->exit();
        delete subState;
        subState = newSubstate;
        subState->entry();
    }
    return nullptr;
}

//substate change
// State* Operating::forward() {
//     State* newSubstate = subState->forward();
//     if(newSubstate != nullptr) {
//         subState->exit();
//         delete subState;
//         subState = newSubstate;
//         subState->entry();
//     }
//     return nullptr;
// }

//explicit exit
// State* Operating::service() {
//     State* newSubstate = subState->service();
//     if(newSubstate != nullptr) {
//         return newSubstate;
//     }
//     return nullptr;
// }
