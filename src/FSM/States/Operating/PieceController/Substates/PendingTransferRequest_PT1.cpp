#include "PendingTransferRequest_PT1.h"

//================================================= constructors & destructors =================================================
PendingTransferRequest_PT1::PendingTransferRequest_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

PendingTransferRequest_PT1::~PendingTransferRequest_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PendingTransferRequest_PT1::entry(){
	PRINT_STATE;
	 data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::REQUEST_TRANSFER);
}

void PendingTransferRequest_PT1::exit(){
	PRINT_STATE;
}

State* PendingTransferRequest_PT1::clone(){
	return new PendingTransferRequest_PT1(data, localdata_);
}


State* PendingTransferRequest_PT1::fbm_2_busy() {
	data->timer->start_timer(500, TIMER_ID::PENDINGTRANSFERREQUEST_PT1);
	return nullptr;
}

State* PendingTransferRequest_PT1::fbm_2_ready() {
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.id);
	return new Transfer_PT1(data, localdata_);
}

State* PendingTransferRequest_PT1::timer(TIMER_ID id) {
	return new PendingTransferRequest_PT1(data, localdata_);
	
}