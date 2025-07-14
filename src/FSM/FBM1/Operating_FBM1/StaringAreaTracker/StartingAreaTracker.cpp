#include "StartingAreaTracker.h"




//================================================= constructors & destructors =================================================
StartingAreaTracker::StartingAreaTracker(ContextData* data) : HState(data, new StartingAreaUnblocked(data)) {
    //substate = new SubState(data);
}

StartingAreaTracker::StartingAreaTracker(ContextData* data, State* initial_substate) : HState(data, initial_substate) 
{}

StartingAreaTracker::~StartingAreaTracker() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartingAreaTracker::entry(){
	PRINT_STATE;
    HState::entry();
}

void StartingAreaTracker::exit(){
    HState::exit();
	PRINT_STATE;
}

State* StartingAreaTracker::clone() {
    return new StartingAreaTracker(data, substate->clone());
}