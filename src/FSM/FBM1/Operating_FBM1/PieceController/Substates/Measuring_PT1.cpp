#include "Measuring_PT1.h"

//================================================= constructors & destructors =================================================
Measuring_PT1::Measuring_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

Measuring_PT1::~Measuring_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Measuring_PT1::entry() {
	PRINT_STATE;

}

void Measuring_PT1::exit() {
	PRINT_STATE;
}

State* Measuring_PT1::clone() {
	return new Measuring_PT1(data, localdata_);
}

State* Measuring_PT1::laser_sorting_gate_blocked() {
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;

	if(current_area == Area::GATE) {
		printf("Typisierung schief gelaufen\n");
		data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.piece->id);
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
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.piece->id);
	Piece* piece = localdata_.piece;
	piece->piece_tracker->update_distance_force(Area::ADC_GATE, 0);
	data->piece_near_adc = false;
	return new ADCGate_PT1(data, localdata_);
}
