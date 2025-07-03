#include "Transfer_PT1.h"

//================================================= constructors & destructors =================================================
Transfer_PT1::Transfer_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

Transfer_PT1::~Transfer_PT1() {}

//===================================================== private functions =====================================================


void Transfer_PT1::send_transfer_start() {
	PieceEnum validated_piece = localdata_.validated_type;
	COM_Enum transfer_enum = COM_Enum::TRANSFER_START_OTHER;
	switch(validated_piece){
		case PieceEnum::FLAT:
			transfer_enum = COM_Enum::TRANSFER_START_FLAT;
			break;
		case PieceEnum::TALL:
			transfer_enum = COM_Enum::TRANSFER_START_TALL;
			break;
		case PieceEnum::TALL_WITH_METAL:
			transfer_enum = COM_Enum::TRANSFER_START_TALL_W_METAL;
			break;
		default:
			break;
	}
	data->sender->send_event((int8_t) Topic::COM, (int) transfer_enum);
}


//===================================================== public functions =====================================================
void Transfer_PT1::entry(){
	PRINT_STATE;
	send_transfer_start();
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

State* Transfer_PT1::transfer_failed() {
	return new PieceMissing_PT1(data, localdata_);
}
