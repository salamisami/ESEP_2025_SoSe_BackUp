#include "PiecesTooClose.h"



//================================================= constructors & destructors =================================================
PiecesTooClose::PiecesTooClose(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PiecesTooClose::~PiecesTooClose() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PiecesTooClose::entry(){
	PRINT_STATE;
    
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::PIECES_TOO_CLOSE);
}

void PiecesTooClose::exit(){
    
	PRINT_STATE;
}


State* PiecesTooClose::error_pieces_too_close_fixed()
{
    return new StartingAreaUnblocked(data);
}

State* PiecesTooClose::clone() {
    return new PiecesTooClose(data);
}