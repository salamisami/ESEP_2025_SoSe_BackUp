#include "BothEstopPressed.h"

//================================================= contructors & destructors =================================================
BothEstopPressed::BothEstopPressed(ContextData* data) : State(data) {}

BothEstopPressed::~BothEstopPressed() {}

//===================================================== private functions =====================================================

//void BothEstopPressed::privateFunction(){}

//===================================================== public functions =====================================================

void BothEstopPressed::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void BothEstopPressed::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* BothEstopPressed::button_estop_released(){
    return new EStopViaNeighbor(data);
}

I_State* BothEstopPressed::com_button_estop_released(){
    return new EStopViaLocal(data);
}