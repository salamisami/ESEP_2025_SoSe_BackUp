#include "PieceTall.h"

//================================================= constructors & destructors =================================================
PieceTall::PieceTall(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceTall::~PieceTall() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceTall::entry(){
	PRINT_STATE;
}

void PieceTall::exit(){
	PRINT_STATE;
}

State* PieceTall::clone(){
	return new PieceTall(data);
}

State* PieceTall::check_piece() {
	if (data->actual_piece == Piece::TALL) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::LET_THROUGH);
		return new PieceTallWithMetal(data);
	}
	if (data->is_ramp_full) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT_FBM2);
	} else {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT);
	}
	return nullptr;
	//return new PieceTall(data);
}

State *PieceTall::reset_to_flat() {
	return new PieceFlat(data);
}

State *PieceTall::reset_to_tall_w_metal() {
	return new PieceTallWithMetal(data);
}
