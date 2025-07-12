#include "MovingToEnd_PT1.h"

//================================================= constructors & destructors =================================================
MovingToEnd_PT1::MovingToEnd_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

MovingToEnd_PT1::~MovingToEnd_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MovingToEnd_PT1::entry() {
	PRINT_STATE;
}

void MovingToEnd_PT1::exit() {
	PRINT_STATE;
}

State* MovingToEnd_PT1::clone() {
	return new MovingToEnd_PT1(data, localdata_);
}

State* MovingToEnd_PT1::laser_back_blocked() {
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;

	if(current_area == Area::GATE_END) {
		send_transfer_start();
		data->sender->send_event((int8_t) Topic::ID, (int) localdata_.piece->id);
		DEBUG("ID is sent to fbm2");
		DEBUG(localdata_.piece->id);
		return new Transfer_PT1(data, localdata_);
	}
	return nullptr;
}


void MovingToEnd_PT1::send_transfer_start() {
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
	DEBUG("Transfer start event is sent");
	data->sender->send_event((int8_t) Topic::COM, (int) transfer_enum);
} 