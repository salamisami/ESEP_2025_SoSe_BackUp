#include "ComRampFull.h"



//================================================= constructors & destructors =================================================
ComRampFull::ComRampFull(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

ComRampFull::~ComRampFull() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ComRampFull::entry(){
    //data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
	PRINT_STATE;
    //TODO CODE
}

void ComRampFull::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* ComRampFull::com_ramp_not_full()
{
    return new NoRampFull(data);
}

State* ComRampFull::ramp_full()
{
    return new BothRampsFull(data);
}

State* ComRampFull::clone() {
    return new ComRampFull(data);
}
