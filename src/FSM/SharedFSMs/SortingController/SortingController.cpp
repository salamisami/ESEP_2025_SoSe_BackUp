#include "SortingController.h"


//================================================= constructors & destructors =================================================
SortingController::SortingController(ContextData* data) : HState(data, new IdleSorting(data)){}
SortingController::SortingController(ContextData* data, State* initial_state) : HState(data, initial_state) {}

SortingController::~SortingController() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SortingController::entry() {
	PRINT_STATE;
	
	HState::entry();
}

void SortingController::exit() {
	HState::exit();
	PRINT_STATE;
}

State* SortingController::clone(){
  return new SortingController(data, substate->clone());
}
