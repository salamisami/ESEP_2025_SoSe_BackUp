#include "Transfer_PT1.h"

//================================================= constructors & destructors =================================================
Transfer_PT1::Transfer_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

Transfer_PT1::~Transfer_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Transfer_PT1::entry(){
	PRINT_STATE;
	//TODO which one?
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::TRANSFER_START_OTHER);
}

void Transfer_PT1::exit(){
	PRINT_STATE;
}

State* Transfer_PT1::clone(){
	return new Transfer_PT1(data, localdata_);
}

State* Transfer_PT1::transfer_done() {
	data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.id);
	return State::EXIT_STATE;
}