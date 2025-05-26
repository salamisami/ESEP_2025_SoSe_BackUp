#include "Traffic_Green_On_Slow.h"

//================================================= contructors & destructors =================================================
Traffic_Green_On_Slow::Traffic_Green_On_Slow(ContextData* data) :State(data) {

}

Traffic_Green_On_Slow::~Traffic_Green_On_Slow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Traffic_Green_On_Slow::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    //TODO blink slow
}

void Traffic_Green_On_Slow::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Traffic_Green_On_Slow::button_start_pressed(){
    return new Waiting(data);
}