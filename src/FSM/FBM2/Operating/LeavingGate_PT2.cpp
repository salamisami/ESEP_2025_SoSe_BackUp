#include "LeavingGate_PT2.h"

//================================================= constructors & destructors =================================================
LeavingGate_PT2::LeavingGate_PT1(ContextData* data) : State(data){
    //substate = new SubState(data);
}

LeavingGate_PT2::~LeavingGate_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void LeavingGate_PT2::entry(){
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::LEAVINGGATE_PT1);
}

void LeavingGate_PT2::exit(){
	PRINT_STATE;
	
}

State* LeavingGate_PT2::clone(){
	return new LeavingGate_PT1(data);
}

State* LeavingGate_PT2::laser_sorting_gate_unblocked() {
	//Piece* piece = localdata_.piece;
	piece->piece_tracker->update_distance_force(Area::GATE_END, 0);
	return new GateEnd(data);
}

State* LeavingGate_PT2::timer(TIMER_ID id) {
	if(id != TIMER_ID::LEAVINGGATE_PT1){
		return nullptr;
	}

	Piece* piece = localdata_.piece;
	Area current_area = piece->piece_tracker->get_distance().first;
	if(current_area == Area::GATE){
		return new LeavingGate_PT2(data, localdata_);
	}

	if(current_area == Area::GATE_END){
		return new GateEnd(data, localdata_);
	}

	DEBUG("PieceMissing! Cause: piece is too long in leaving the Gate.");
	data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_LOST);
	//data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.piece->id);
	//PieceEnum validated_piece = localdata_.validated_type;
	switch(validated_piece) {
		case PieceEnum::FLAT:
			data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_FLAT);
			break;
		case PieceEnum::TALL:
			data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL);
			break;
		case PieceEnum::TALL_WITH_METAL:
			data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL_W_METAL);
			break;
		default:
			break;
	}
	//Piece* piece_to_delete = localdata_.piece;
	data->pieces_map->erase(localdata_.piece->id);
	delete piece_to_delete;
	return State::EXIT_STATE;
}