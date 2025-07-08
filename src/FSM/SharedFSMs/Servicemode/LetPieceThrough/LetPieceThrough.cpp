#include "LetPieceThrough.h"

//================================================= constructors & destructors =================================================
LetPieceThrough::LetPieceThrough(ContextData* data, int duration)
: HState(data, new IdleLPT(data, duration)){
    //substate = new SubState(data);
}

LetPieceThrough::LetPieceThrough(ContextData* data, State* initial_substate) : HState(data, initial_substate) 
{}

LetPieceThrough::~LetPieceThrough() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void LetPieceThrough::entry(){
	PRINT_STATE;
    HState::entry();
}

void LetPieceThrough::exit(){
    HState::exit();
    PRINT_STATE;
}

State* LetPieceThrough::clone() {
    return new LetPieceThrough(data, substate->clone());
}