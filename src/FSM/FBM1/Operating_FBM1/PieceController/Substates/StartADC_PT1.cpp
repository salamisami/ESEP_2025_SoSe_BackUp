#include "StartADC_PT1.h"

//================================================= constructors & destructors =================================================
StartADC_PT1::StartADC_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
	//substate = new SubState(data);
}

StartADC_PT1::~StartADC_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StartADC_PT1::entry() {
	PRINT_STATE;
	data->timer->start_timer(UPDATE_PIECE_INTERVAL, TIMER_ID::STARTADC_PT1);
	data->piece_near_adc = true;
}

void StartADC_PT1::exit() {
	PRINT_STATE;
}

State* StartADC_PT1::clone() {
	return new StartADC_PT1(data, localdata_);
}

State* StartADC_PT1::timer(TIMER_ID id) {
	if(id != TIMER_ID::STARTADC_PT1) {
		return nullptr;
	}
	Piece* piece = localdata_.piece;

	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;
	auto current_position = distance.second;

	switch(current_area) {
		case Area::START_ADC:
			if(current_position > DISTANCE_BETWEEN_PIECES && !localdata_.unblock_signal_has_been_sent) {
				localdata_.unblock_signal_has_been_sent = true;
				data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::UNBLOCK_STARTING_AREA);
				return new StartADC_PT1(data, localdata_);
			}

			if(current_position >= MOTOR_SLOW_POS_AT_START_ADC) {
				data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
				data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) localdata_.piece->id);
				localdata_.unblock_signal_has_been_sent = false;
				return new ADC_PT1(data, localdata_);
			}
			return new StartADC_PT1(data, localdata_);
		default:
			break;
	}
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
	data->sender->send_event((int8_t) Topic::MOTOR_SLOW, (int) localdata_.piece->id);
	localdata_.unblock_signal_has_been_sent = false;
	return new ADC_PT1(data, localdata_);
}

// State* StartADC_PT1::timer(TIMER_ID id) {
// 	if(id != TIMER_ID::STARTADC_PT1) {
// 		return nullptr;
// 	}
// 	Piece* piece = localdata_.piece;

// 	auto distance = piece->piece_tracker->get_distance();
// 	Area current_area = distance.first;
// 	auto current_position = distance.second;

// 	switch(current_area) {
// 		case Area::START_ADC:
// 			if(current_position > DISTANCE_BETWEEN_PIECES){ // && !localdata_.unblock_signal_has_been_sent) { 
// 				piece->piece_tracker->print_distance();
// 				data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::UNBLOCK_STARTING_AREA);
// 				localdata_.unblock_signal_has_been_sent = true;
// 				return new StartADC_PT1(data, localdata_);
// 			}
// 			if(current_position > 100 - PIECE_TRANSITION_TOLERANCE){
// 				return new ADC_PT1(data, localdata_);
// 			}
// 		case Area::ADC:
// 			return new ADC_PT1(data, localdata_);
// 			break;
// 		default:
// 			break;
// 	}
// 	return new StartADC_PT1(data, localdata_);
// }
