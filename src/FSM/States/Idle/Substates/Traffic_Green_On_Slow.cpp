#include "Traffic_Green_On_Slow.h"

//================================================= constructors & destructors =================================================
Traffic_Green_On_Slow::Traffic_Green_On_Slow(ContextData* data) :State(data) {

}

Traffic_Green_On_Slow::~Traffic_Green_On_Slow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Traffic_Green_On_Slow::entry() {
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_SLOW);
}

void Traffic_Green_On_Slow::exit() {
    PRINT_STATE;
}

State* Traffic_Green_On_Slow::button_start_pressed(){
    return new Waiting(data);
}