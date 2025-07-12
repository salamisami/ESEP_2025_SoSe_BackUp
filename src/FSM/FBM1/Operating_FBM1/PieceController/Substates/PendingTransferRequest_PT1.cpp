#include "PendingTransferRequest_PT1.h"

//================================================= constructors & destructors =================================================
PendingTransferRequest_PT1::PendingTransferRequest_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

PendingTransferRequest_PT1::~PendingTransferRequest_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PendingTransferRequest_PT1::entry() {
	PRINT_STATE;
	data->timer->start_timer(500, TIMER_ID::PENDINGTRANSFERREQUEST_PT1);
	data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, localdata_.piece->id);
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::REQUEST_TRANSFER);
}

void PendingTransferRequest_PT1::exit() {
	PRINT_STATE;
}

State* PendingTransferRequest_PT1::clone() {
	return new PendingTransferRequest_PT1(data, localdata_);
}


State* PendingTransferRequest_PT1::fbm_2_busy() {
	return nullptr;
}

State* PendingTransferRequest_PT1::fbm_2_ready() {
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.piece->id);
	send_transfer_start();
	data->sender->send_event((int8_t) Topic::ID, (int) localdata_.piece->id);
	return new Transfer_PT1(data, localdata_);
}

State* PendingTransferRequest_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::PENDINGTRANSFERREQUEST_PT1) {
		return nullptr;
	}
	return new PendingTransferRequest_PT1(data, localdata_);
}

void PendingTransferRequest_PT1::send_transfer_start() {
	PieceEnum validated_piece = localdata_.validated_type;
	COM_Enum transfer_enum = COM_Enum::TRANSFER_START_OTHER;
	switch(validated_piece) {
		case PieceEnum::FLAT:
			if(localdata_.sort_out_fbm2) {
				transfer_enum = COM_Enum::TRANSFER_START_FLAT_SORT_OUT;
			} else {
				transfer_enum = COM_Enum::TRANSFER_START_FLAT;
			}
			break;
		case PieceEnum::TALL:
			if(localdata_.sort_out_fbm2) {
				transfer_enum = COM_Enum::TRANSFER_START_TALL_SORT_OUT;
			} else {
				transfer_enum = COM_Enum::TRANSFER_START_TALL;
			}
			break;
		case PieceEnum::TALL_WITH_METAL:
			if(localdata_.sort_out_fbm2) {
				transfer_enum = COM_Enum::TRANSFER_START_TALL_W_METAL_SORT_OUT;
			} else {
				transfer_enum = COM_Enum::TRANSFER_START_TALL_W_METAL;
			}
			break;
		default:
			break;
	}
	data->sender->send_event((int8_t) Topic::COM, (int) transfer_enum);
}