#include "ADC_Gate.h"

//================================================= constructors & destructors =================================================
ADC_Gate::ADC_Gate(ContextData* data) : State(data) {}

//HState
//ADC_Gate::ADC_Gate(ContextData* data) : HState(data, new SubState(data), <default_next_state> ) {}
//ADC_Gate::ADC_Gate(ContextData* data, State* initial_substate) : HState(data, initial_substate, <default_next_state>) {}

//OrthState
//ADC_Gate::ADC_Gate(ContextData* data) : OrthState(data, {new State1(data), new State2(data)}, <default_next_state> ) {}
//ADC_Gate::ADC_Gate(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates, <default_next_state>) {}

ADC_Gate::~ADC_Gate() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADC_Gate::entry() {
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::ADC_GATE);
	//Action here
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
}

void ADC_Gate::exit() {
	//HState::entry() //for HState
	//OrthState::entry() //for OrthState
	//Action here
	PRINT_STATE;
}

State* ADC_Gate::clone() {
	//return new ADC_Gate(data, substate->clone()); //for HState
	//return new ADC_Gate(data, substates_clone()); //for OrthState
	return new ADC_Gate(data);
}

State* ADC_Gate::request_transfer() {
	data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_BUSY);
	return nullptr;
}
State* ADC_Gate::laser_back_blocked() {
	return new Pieceappeared(data);
}
State* ADC_Gate::laser_front_blocked() {
	return new Pieceappeared(data);
}
State* ADC_Gate::laser_ramp_blocked() {
	return new Pieceappeared(data);
}
State* ADC_Gate::laser_sorting_gate_blocked() {
	auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	auto validated_piece = validate_piece(data->scanned_piece_FBM2, data->scanned_piece_has_metal_fbm2);

	if(data->piece_FBM2_soll->type == validated_piece) {
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::LET_THROUGH);
		DEBUG("Verdict: Piece let through");
		data->scanned_piece_has_metal_fbm2 = false;
		return new LeavingGate_PT2(data);
	}
	data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::SORTING_OUT_FBM2);
	DEBUG("Verdict: Piece sort out.");
	data->scanned_piece_has_metal_fbm2 = false;
	return new Sorting_out(data);
}

State* ADC_Gate::timer(TIMER_ID id) {
	if(id != TIMER_ID::ADC_GATE) {
		return nullptr;
	}
	auto distance = data->piece_FBM2_soll->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	//piece->piece_tracker->print_distance();

	switch(current_area){
		case Area::ADC_GATE:
			return new ADC_Gate(data);
			break;
		case Area::GATE:
			if(current_pos < PIECE_TRANSITION_TOLERANCE){
				return new ADC_Gate(data);
			}
			break;
		default:
			break;
	}
	return new Piece_Missing(data);
}
State* ADC_Gate::metal_detected() {
	data->scanned_piece_has_metal_fbm2 = true;
	return nullptr;
}

PieceEnum ADC_Gate::validate_piece(const ScannedPiece& scanned_piece, const bool& has_metal) {
	printf("Gate_PT2: scanned piece: %d, is metal: %d\n", (int) scanned_piece, (int) has_metal);
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
	printf("Gate_PT2: predicted_piece: %d\n", (int) predicted_piece);
	return predicted_piece;
}
