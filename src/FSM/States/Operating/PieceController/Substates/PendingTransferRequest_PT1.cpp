#include "PendingTransferRequest_PT1.h"

//================================================= constructors & destructors =================================================
PendingTransferRequest_PT1::PendingTransferRequest_PT1(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PendingTransferRequest_PT1::~PendingTransferRequest_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PendingTransferRequest_PT1::entry(){
	PRINT_STATE;
}

void PendingTransferRequest_PT1::exit(){
	PRINT_STATE;
}

State* PendingTransferRequest_PT1::clone(){
	return new PendingTransferRequest_PT1(data);
}