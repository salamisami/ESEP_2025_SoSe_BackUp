#include "ADCGate_PT1.h"

//================================================= constructors & destructors =================================================
ADCGate_PT1::ADCGate_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata_) {
    //substate = new SubState(data);
}

ADCGate_PT1::~ADCGate_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ADCGate_PT1::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.id);
	data->timer->start_timer(100, TIMER_ID::ADCGATE_PT1);
}

void ADCGate_PT1::exit(){
	PRINT_STATE;
}

State* ADCGate_PT1::clone(){
	return new ADCGate_PT1(data, localdata_);
}

State* ADCGate_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::ADCGATE_PT1){
		return nullptr;
	}
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area != Area::ADC_GATE){
		return new PieceMissing_PT1(data, localdata_);
	} 
	return new ADCGate_PT1(data, localdata_);
}


State* ADCGate_PT1::laser_sorting_gate_blocked() {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area == Area::GATE){
		return new Gate_PT1(data, localdata_);
	}
}

State* ADCGate_PT1::metal_detected() {
	auto piece = data->pieces_map->at(localdata_.id);
	Area current_area = piece->piece_tracker.getArea();
	int current_position = piece->piece_tracker.getPosition();

	if(current_area == Area::GATE){
		return new IsMetal_PT1(data, localdata_);
	}
	return nullptr;
}