#include "StartingAreaBlocked.h"



//================================================= constructors & destructors =================================================
StartingAreaBlocked::StartingAreaBlocked(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StartingAreaBlocked::~StartingAreaBlocked() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartingAreaBlocked::entry(){
	PRINT_STATE;
    //TODO CODE
}

void StartingAreaBlocked::exit(){
    //TODO CODE
	PRINT_STATE;
}


State* StartingAreaBlocked::laser_front_blocked()
{
    return new StartingAreaBlocked(data);
}

State* StartingAreaBlocked::unblock_starting_area()
{
    return new StartingAreaUnblocked(data);
}
