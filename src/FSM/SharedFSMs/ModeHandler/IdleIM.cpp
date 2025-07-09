#include "IdleIM.h"
//===================================================== public functions =====================================================
void IdleIM::entry() {
    data->sender->send_event((int8_t) Topic::Actuator, (int) ActuatorEnum::LED_START_ON);
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON_SLOW);
}

void IdleIM::exit() {
    data->sender->send_event((int8_t) Topic::Actuator, (int) ActuatorEnum::LED_START_OFF);
    PRINT_STATE;
}

State* IdleIM::button_start_pressed(){
    return new WaitingIM(data);
}

State* IdleIM::clone() {
    return new IdleIM(data);
}
