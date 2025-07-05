#include "NoRampFull.h"



//================================================= constructors & destructors =================================================
NoRampFull::NoRampFull(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

NoRampFull::~NoRampFull() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void NoRampFull::entry(){
	PRINT_STATE;
    //TODO CODE
}

void NoRampFull::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* NoRampFull::ramp_full()
{
    return new LocalRampFull(data);
}

State* NoRampFull::com_ramp_full()
{
    return new ComRampFull(data);
}

State* NoRampFull::clone() {
    return new NoRampFull(data);
}