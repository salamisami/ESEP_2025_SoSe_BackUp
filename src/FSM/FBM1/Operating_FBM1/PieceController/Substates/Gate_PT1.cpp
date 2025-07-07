#include "Gate_PT1.h"

//================================================= constructors & destructors =================================================
Gate_PT1::Gate_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

Gate_PT1::~Gate_PT1() {}

//===================================================== private functions =====================================================

PieceEnum Gate_PT1::validate_piece(const ScannedPiece& scanned_piece, const bool& has_metal) {
	PieceEnum predicted_piece = PieceEnum::UNKNOWN;
	if(has_metal) {
		switch(scanned_piece) {
			case ScannedPiece::HOLE:
				predicted_piece = PieceEnum::TALL_WITH_METAL;
				break;
			default:
				break;
		}
	} else {
		switch(scanned_piece) {
			case ScannedPiece::FLAT:
				predicted_piece = PieceEnum::FLAT;
				break;
			case ScannedPiece::HOLE:
				predicted_piece = PieceEnum::TALL;
			default:
				break;
		}
	}
	return predicted_piece;
}

//===================================================== public functions =====================================================
void Gate_PT1::entry() {
	auto piece = data->pieces_map->at(localdata_.id);
	piece->piece_tracker->update_distance_force(Area::GATE, 0);
	localdata_.validated_type = validate_piece(localdata_.ist_type, localdata_.is_metal);
	data->sender->send_event((int8_t)Topic::CHECK_PIECE, (int) localdata_.validated_type);
	PRINT_STATE;
}

void Gate_PT1::exit() {
	PRINT_STATE;
}

State* Gate_PT1::clone() {
	return new Gate_PT1(data, localdata_);
}

State* Gate_PT1::sort_out() {
	return new SortingOut_PT1(data, localdata_);
}
State* Gate_PT1::let_through() {
	localdata_.sort_out_fbm2 = false;
	return new GateEnd_PT1(data, localdata_);
}
State* Gate_PT1::sort_out_fbm2() {
	localdata_.sort_out_fbm2 = true;
	return new GateEnd_PT1(data, localdata_);
}
