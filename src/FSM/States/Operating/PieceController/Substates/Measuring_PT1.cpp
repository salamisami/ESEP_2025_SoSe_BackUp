#include "Measuring_PT1.h"

//================================================= constructors & destructors =================================================
Measuring_PT1::Measuring_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

Measuring_PT1::~Measuring_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Measuring_PT1::entry(){
	PRINT_STATE;
	data->piece_near_adc = false;
}

void Measuring_PT1::exit(){
	PRINT_STATE;
}

State* Measuring_PT1::clone(){
	return new Measuring_PT1(data, localdata_);
}

State* Measuring_PT1::laser_sorting_gate_blocked() {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area == Area::GATE){
		DEBUG("Typisierung schief gelaufen");
		return new Gate_PT1(data, localdata_);
	}

	return nullptr;
}

State* Measuring_PT1::adc_wh_detect() {
	localdata_.ist_type = ScannedPiece::TALL;
	return goto_adcgate();
}

State* Measuring_PT1::adc_wf_detect() {
	localdata_.ist_type = ScannedPiece::FLAT;
	return goto_adcgate();
}

State* Measuring_PT1::adc_w_b_detect() {
	localdata_.ist_type = ScannedPiece::HOLE;
	return goto_adcgate();
}

State* Measuring_PT1::adc_w_not_detect() {
	return goto_adcgate();
}

State* Measuring_PT1::adc_invalid_measure() {
	return goto_adcgate();
}

State* Measuring_PT1::goto_adcgate() {
	return new ADCGate_PT1(data, localdata_);
}
