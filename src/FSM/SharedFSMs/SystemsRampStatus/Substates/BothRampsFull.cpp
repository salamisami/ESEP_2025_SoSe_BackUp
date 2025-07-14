#include "BothRampsFull.h"



//================================================= constructors & destructors =================================================
BothRampsFull::BothRampsFull(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

BothRampsFull::~BothRampsFull() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void BothRampsFull::entry(){
	PRINT_STATE;
    
}

void BothRampsFull::exit(){
    
	PRINT_STATE;
}

State* BothRampsFull::com_ramp_not_full()
{
    return new LocalRampFull(data);
}

State* BothRampsFull::ramp_not_full()
{
    return new ComRampFull(data);
}

State* BothRampsFull::sorting_out()
{
    data->sender->send_event((int8_t)Topic::ERROR, (int) Error_Enum::ERROR_BOTH_R_FULL);
    return new BothRampsFull(data);
}

State* BothRampsFull::error_both_r_full()
{
    return new BothRampsFull(data);
}

State* BothRampsFull::clone() {
    return new BothRampsFull(data);
}