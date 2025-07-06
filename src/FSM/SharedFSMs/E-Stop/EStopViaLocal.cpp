#include "EStopViaLocal.h"

//================================================= constructors & destructors =================================================
EStopViaLocal::EStopViaLocal(ContextData* data) : State(data){}

EStopViaLocal::~EStopViaLocal() {}

//===================================================== private functions =====================================================

//void EStopViaLocal::privateFunction(){}

//===================================================== public functions =====================================================

void EStopViaLocal::entry(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void EStopViaLocal::exit(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
}

State* EStopViaLocal::clone(){
	return new EStopViaLocal(data);
}

State* EStopViaLocal::com_button_estop_pressed(){
    return new BothEstopPressed(data);
}

State* EStopViaLocal::button_estop_released(){
    return new EStopReleased(data);
}
