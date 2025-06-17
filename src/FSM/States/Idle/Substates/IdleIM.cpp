#include "IdleIM.h"

//================================================= constructors & destructors =================================================
IdleIM::IdleIM(ContextData* data) :State(data) {

}

IdleIM::~IdleIM() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleIM::entry() {
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_SLOW);
}

void IdleIM::exit() {
    PRINT_STATE;
}

State* IdleIM::button_start_pressed(){
    return new WaitingIM(data);
}