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

	//piece->piece_tracker->print_distance();

//	if(current_area == Area::ADC_GATE && current_pos < PIECE_TRANSITION_TOLERANCE){
//		return new ADCGate_PT1(data, localdata_);
//	}
//
//	if(current_area == Area::ADC_GATE && current_pos >= PIECE_TRANSITION_TOLERANCE){
//		return new ADCGate_PT1(data, localdata_);
//	}
//
//	if(current_area == Area::GATE && current_pos < PIECE_TRANSITION_TOLERANCE){
//		return new ADCGate_PT1(data, localdata_);
//	}

	if (current_area == Area::GATE_END && current_pos >= PIECE_TRANSITION_TOLERANCE){
	DEBUG("PieceMissing! Cause: piece is too long in ADC -> Gate.");
	MACRO_PIECE_MISSING_PT1
	}
	return new ADCGate_PT1(data, localdata_);
}

State* ADCGate_PT1::laser_sorting_gate_blocked() {
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;
	if(current_area == Area::GATE || current_area == Area::ADC_GATE){
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
	return nullptr;
}

State* ADCGate_PT1::metal_detected() {
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_pos = distance.second;

	if(current_area == Area::ADC_GATE && current_pos < PIECE_TRANSITION_TOLERANCE) {
		return nullptr;
	}

	//before expected
	if(current_area == Area::ADC_GATE && current_pos >= (100 - PIECE_TRANSITION_TOLERANCE)) {
		return new IsMetal_PT1(data, localdata_);
	}

	if(current_area == Area::GATE && current_pos < PIECE_TRANSITION_TOLERANCE) {
		return new IsMetal_PT1(data, localdata_);
	}
	return nullptr;
}
