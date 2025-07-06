#include "StartingAreaUnblocked.h"



//================================================= constructors & destructors =================================================
StartingAreaUnblocked::StartingAreaUnblocked(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartingAreaUnblocked::~StartingAreaUnblocked() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartingAreaUnblocked::entry(){
	PRINT_STATE;
    //TODO CODE
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_Q2_ON);
}

void StartingAreaUnblocked::exit(){
    //TODO CODE
	PRINT_STATE;
}


State* StartingAreaUnblocked::laser_front_blocked()
{
    return new StartingAreaBlocked(data);
}

State* StartingAreaUnblocked::clone() {
    return new StartingAreaUnblocked(data);
}
