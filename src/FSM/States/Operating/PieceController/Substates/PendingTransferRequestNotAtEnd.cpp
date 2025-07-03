#include "PendingTransferRequestNotAtEnd.h"

//================================================= constructors & destructors =================================================
PendingTransferRequestNotAtEnd::PendingTransferRequestNotAtEnd(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PendingTransferRequestNotAtEnd::~PendingTransferRequestNotAtEnd() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PendingTransferRequestNotAtEnd::entry(){
	PRINT_STATE;
}

void PendingTransferRequestNotAtEnd::exit(){
	PRINT_STATE;
}

State* PendingTransferRequestNotAtEnd::clone(){
	return new PendingTransferRequestNotAtEnd(data);
}