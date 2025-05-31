#include "Idle.h"

//================================================= contructors & destructors =================================================
Idle::Idle(ContextData* data, State* initial_substate) : State(data) {
    if(initial_substate == nullptr) {
        substate = new Traffic_Green_On_Slow(data);
    } else {
        substate = initial_substate;
    }
}

Idle::~Idle() {
}

//===================================================== private functions =====================================================




//===================================================== public functions =====================================================

void Idle::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    substate->entry();
}

void Idle::exit() {
    substate->exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Idle::button_start_pressed(){
    State* newSubstate = substate->button_start_pressed();
    if(newSubstate != nullptr){
        //there is a substate change, change only the substate
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
    }
    return nullptr;
}
State* Idle::button_start_released(){
    State* newSubstate = substate->button_start_released();
    if(newSubstate != nullptr){
        //there is a substate change, explicit exit
        return newSubstate;
    }
    return nullptr;
}

State* Idle::timer(int id){
    State* newSubstate = substate->timer(id);
    if(newSubstate != nullptr) {
        substate->exit();
        delete substate;
        substate = newSubstate;
        substate->entry();
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
