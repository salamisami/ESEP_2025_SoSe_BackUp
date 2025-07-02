#include "PieceFlat.h"

//================================================= constructors & destructors =================================================
PieceFlat::PieceFlat(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceFlat::~PieceFlat() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceFlat::entry(){
	PRINT_STATE;
}

void PieceFlat::exit(){
	PRINT_STATE;
}

State* PieceFlat::clone() {
	return new PieceFlat(data);
}


State* PieceFlat::check_piece() {
	if (data->actual_piece == Piece::FLAT) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::LET_THROUGH);
		return new PieceTall(data);
	}
	if (data->is_ramp_full) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT_FBM2);
	} else {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT);
	}
	return nullptr;
	//return new PieceFlat(data);
}
State *PieceFlat::reset_to_tall_w_metal() {
	return new PieceTallWithMetal(data);
}

State *PieceFlat::reset_to_tall() {
	return new PieceTall(data);
}
