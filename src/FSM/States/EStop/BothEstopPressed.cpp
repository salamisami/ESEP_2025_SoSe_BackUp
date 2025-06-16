#include "BothEstopPressed.h"

//================================================= constructors & destructors =================================================
BothEstopPressed::BothEstopPressed(ContextData* data) : State(data) {}

BothEstopPressed::~BothEstopPressed() {}

//===================================================== private functions =====================================================

//void BothEstopPressed::privateFunction(){}

//===================================================== public functions =====================================================

void BothEstopPressed::entry(){
    PRINT_STATE;
}
void BothEstopPressed::exit(){
    PRINT_STATE;
}

State* BothEstopPressed::button_estop_released(){
    return new EStopViaNeighbor(data);
}

State* BothEstopPressed::com_button_estop_released(){
    return new EStopViaLocal(data);
}