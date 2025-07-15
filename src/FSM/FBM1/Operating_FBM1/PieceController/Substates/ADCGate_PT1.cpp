#include "ADCGate_PT1.h"



//================================================= constructors & destructors =================================================
ADCGate_PT1::ADCGate_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

ADCGate_PT1::~ADCGate_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCGate_PT1::entry() {
	PRINT_STATE;
	data->timer->start_timer(UPDATE_PIECE_INTERVAL, TIMER_ID::ADCGATE_PT1);
}

void ADCGate_PT1::exit() {
	PRINT_STATE;
}

State* ADCGate_PT1::clone() {
	return new ADCGate_PT1(data, localdata_);
}

State* ADCGate_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::ADCGATE_PT1) {
		return nullptr;
	}
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	if(current_area == Area::ADC_GATE && data->piece_near_end){
		data->sender->send_event((int8_t) Topic::COM, (int) COM_Enum::REQUEST_TRANSFER);
	}

	if(current_area == Area::GATE_END && current_pos >= PIECE_TRANSITION_TOLERANCE) {
		DEBUG("PieceMissing! Cause: piece is too long in ADC -> Gate.");
		printf("Error: Piece takes too long to leave ADC-Gate.\n");
		MACRO_PIECE_MISSING_PT1
	}
	return new ADCGate_PT1(data, localdata_);
}

State* ADCGate_PT1::laser_sorting_gate_blocked() {
	DEBUG("sorting gate blocked.");

	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;
	if(current_area == Area::GATE || current_area == Area::ADC_GATE) {
		DEBUG("Laser sorting gate is expected. Let's go to Gate_PT1");
		auto piece = localdata_.piece;
		piece->piece_tracker->update_distance_force(Area::GATE, 0);
		localdata_.validated_type = validate_piece(localdata_.ist_type, localdata_.is_metal);
		data->sender->send_event((int8_t) Topic::CHECK_PIECE, (int) localdata_.validated_type);
		return new Gate_PT1(data, localdata_);
	}
	//	if(current_area == Area::ADC_GATE && current_pos < PIECE_TRANSITION_TOLERANCE) {
	//		return nullptr;
	//	}
	//
	//	//before expected
	//	if(current_area == Area::ADC_GATE && current_pos >= (100 - PIECE_TRANSITION_TOLERANCE)) {
	//		return new Gate_PT1(data, localdata_);
	//	}
	//
	//	if(current_area == Area::GATE && current_pos < PIECE_TRANSITION_TOLERANCE) {
	//		return new Gate_PT1(data, localdata_);
	//	}
	DEBUG("This sorting gate is not blocked");
	return nullptr;
}

State* ADCGate_PT1::metal_detected() {
	DEBUG("Metal Detected.");
	printf("Metal Detected.\n");
	localdata_.is_metal = true;
	return nullptr;
}


PieceEnum ADCGate_PT1::validate_piece(const ScannedPiece& scanned_piece, const bool& has_metal) {
	printf("Gate_PT1: scanned piece: %d, is metal: %d\n", (int) scanned_piece, (int) has_metal);
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

State* ADCGate_PT1::fbm_2_ready() {
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.piece->id);
	return nullptr;
}

State* ADCGate_PT1::fbm_2_busy() {
	data->sender->send_event((int8_t) Topic::MOTOR_STOP_FSM, (int) localdata_.piece->id);
	return nullptr;
}


