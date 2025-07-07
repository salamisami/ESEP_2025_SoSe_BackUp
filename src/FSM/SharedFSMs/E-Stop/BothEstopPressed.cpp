#include "BothEstopPressed.h"

//================================================= constructors & destructors =================================================
BothEstopPressed::BothEstopPressed(ContextData* data) : State(data) {}

BothEstopPressed::~BothEstopPressed() {}

//===================================================== private functions =====================================================

//void BothEstopPressed::privateFunction(){}

//===================================================== public functions =====================================================

void BothEstopPressed::entry(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_ON_SLOW);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW);
}
void BothEstopPressed::exit(){
    PRINT_STATE;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

State* BothEstopPressed::clone(){
	return new BothEstopPressed(data);
}

State* BothEstopPressed::button_estop_released(){
    return new EStopViaNeighbor(data);
}

State* BothEstopPressed::com_button_estop_released(){
    return new EStopViaLocal(data);
}
