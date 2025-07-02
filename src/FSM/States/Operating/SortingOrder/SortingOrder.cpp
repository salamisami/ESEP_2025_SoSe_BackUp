#include "SortingOrder.h"

//================================================= constructors & destructors =================================================
SortingOrder::SortingOrder(ContextData* data) : HState(data, new PieceFlat(data)) {}
SortingOrder::SortingOrder(ContextData* data, State* initial_substate) : HState(data, initial_substate) {}

SortingOrder::~SortingOrder() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SortingOrder::entry(){
	PRINT_STATE;
	HState::entry();
}

void SortingOrder::exit(){
	HState::exit();
	PRINT_STATE;
}

State* SortingOrder::clone() {
	return new SortingOrder(data, substate->clone());
}