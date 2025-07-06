#include "TimerReceivedIM.h"

//================================================= constructors & destructors =================================================
TimerReceivedIM::TimerReceivedIM(ContextData* data) :State(data) {}

TimerReceivedIM::~TimerReceivedIM() {}

//===================================================== private functions =====================================================

//void TimerReceivedIM::privateFunction(){}

//===================================================== public functions =====================================================

//void TimerReceivedIM::publicFunction(){}
void TimerReceivedIM::entry(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void TimerReceivedIM::exit(){
    PRINT_STATE;
}

State* TimerReceivedIM::button_start_released(){
    return new Servicemode(data);
}
