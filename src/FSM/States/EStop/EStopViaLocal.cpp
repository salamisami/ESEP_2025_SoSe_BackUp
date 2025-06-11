#include "EStopViaLocal.h"

//================================================= contructors & destructors =================================================
EStopViaLocal::EStopViaLocal(ContextData* data) : State(data){}

EStopViaLocal::~EStopViaLocal() {}

//===================================================== private functions =====================================================

//void EStopViaLocal::privateFunction(){}

//===================================================== public functions =====================================================

void EStopViaLocal::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void EStopViaLocal::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

I_State* EStopViaLocal::com_button_estop_pressed(){
    return new BothEstopPressed(data);
}

I_State* EStopViaLocal::button_estop_released(){
    return new EStopInactive(data);
}
