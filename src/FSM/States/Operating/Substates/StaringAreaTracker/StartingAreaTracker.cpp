#include "StartingAreaTracker.h"




//================================================= constructors & destructors =================================================
StartingAreaTracker::StartingAreaTracker(ContextData* data) : HState(data, new StartingAreaUnblocked(data)) {
    //substate = new SubState(data);
}

StartingAreaTracker::~StartingAreaTracker() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartingAreaTracker::entry(){
	PRINT_STATE;
    //TODO CODE
    HState::entry();
}

void StartingAreaTracker::exit(){
    HState::exit();
    //TODO CODE
	PRINT_STATE;
}