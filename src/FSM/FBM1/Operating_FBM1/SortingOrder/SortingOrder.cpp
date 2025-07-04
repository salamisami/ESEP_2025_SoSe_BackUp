#include "SortingOrder.h"

//================================================= constructors & destructors =================================================
SortingOrder::SortingOrder(ContextData* data) : HState(data, new PieceFlat(data)) {
    //substate = new SubState(data);
}

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
