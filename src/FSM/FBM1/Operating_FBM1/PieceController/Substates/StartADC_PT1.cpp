#include "StartADC_PT1.h"

//================================================= constructors & destructors =================================================
StartADC_PT1::StartADC_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

StartADC_PT1::~StartADC_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartADC_PT1::entry(){
	PRINT_STATE;
	data->timer->start_timer(100, TIMER_ID::STARTADC_PT1);
	data->piece_near_adc = true;
}

void StartADC_PT1::exit(){
	PRINT_STATE;
}

State* StartADC_PT1::clone(){
	return new StartADC_PT1(data, localdata_);
}

State* StartADC_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::STARTADC_PT1){
		return nullptr;
	}
	Piece* piece = data->pieces_map->at(localdata_.id);

	auto distance = piece->piece_tracker.get_distance();
	Area current_area = distance.first;
	auto current_position = distance.second;

	if(current_area != Area::START_ADC){
		return new ADC_PT1(data, localdata_);
	} 

	//TODO calibrate here
	if(current_position > DISTANCE_BETWEEN_PIECES){
		piece->piece_tracker.print_distance();
		data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::UNBLOCK_STARTING_AREA);
	}
	return new StartADC_PT1(data, localdata_);
}