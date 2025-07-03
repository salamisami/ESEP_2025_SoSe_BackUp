#include "PendingTransferRequestNotAtEnd.h"

//================================================= constructors & destructors =================================================
PendingTransferRequestNotAtEnd::PendingTransferRequestNotAtEnd(ContextData* data, LocalDataPT1 localdata)) : State(data) {
    //substate = new SubState(data);
}

PendingTransferRequestNotAtEnd::~PendingTransferRequestNotAtEnd() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PendingTransferRequestNotAtEnd::entry(){
  data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::REQUEST_TRANSFER);
	PRINT_STATE;
}

void PendingTransferRequestNotAtEnd::exit(){
	PRINT_STATE;
}

State* PendingTransferRequestNotAtEnd::clone(){
	return new PendingTransferRequestNotAtEnd(data, localdata_);
}

State* PendingTransferRequestNotAtEnd::fbm_2_busy(){
  WAIT(500);
  return new PendingTransferRequestNotAtEnd(data, localdata_);
} 

State* PendingTransferRequestNotAtEnd::fbm_2_ready(){
  return new MovingToEnd_PT1(data, localdata_);
}

