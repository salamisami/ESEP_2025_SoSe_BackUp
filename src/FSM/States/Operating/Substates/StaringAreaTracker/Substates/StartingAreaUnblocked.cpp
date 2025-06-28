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
}

void StartingAreaUnblocked::exit(){
    //TODO CODE
	PRINT_STATE;
}

State* NoRampFull::laser_front_blocked()
{
    return new StartingAreaBlocked(data);
}
