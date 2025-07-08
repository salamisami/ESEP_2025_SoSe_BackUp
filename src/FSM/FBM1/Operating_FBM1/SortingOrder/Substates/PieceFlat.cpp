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


State* PieceFlat::tall_w_metal_piece() {
	if (data->is_ramp_full) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT_FBM2);
	} else {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT);
	}
	return nullptr;
	//return new PieceFlat(data);
}

State* PieceFlat::tall_piece()  {
	if (data->is_ramp_full) {
		DEBUG("tall_piece: Sorting Order -> PT1: Sort out fbm2");
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT_FBM2);
	} else {
		DEBUG("tall_piece: Sorting Order -> PT1: Sort out");
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT);
	}
	return nullptr;
	//return new PieceFlat(data);
}

State* PieceFlat::flat_piece() {
	DEBUG("flat_piece: Sorting Order -> PT1: let through");
	data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::LET_THROUGH);
	return new PieceTall(data);
}

State* PieceFlat::unknown_piece() {
	if(data->is_ramp_full) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT_FBM2);
	} else {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORT_OUT);
	}
	return nullptr;
	//return new PieceTallWithMetal(data);
}



State *PieceFlat::reset_to_tall_w_metal() {
	return new PieceTallWithMetal(data);
}

State *PieceFlat::reset_to_tall() {
	return new PieceTall(data);
}
