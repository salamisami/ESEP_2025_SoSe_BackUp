#include "MovingToEnd_PT1.h"

//================================================= constructors & destructors =================================================
MovingToEnd_PT1::MovingToEnd_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

MovingToEnd_PT1::~MovingToEnd_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void MovingToEnd_PT1::entry(){
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.piece->id);
	PRINT_STATE;
}

void MovingToEnd_PT1::exit(){
	PRINT_STATE;
}

State* MovingToEnd_PT1::clone(){
	return new MovingToEnd_PT1(data, localdata_);
}

State* MovingToEnd_PT1::laser_back_blocked(){
	auto piece = localdata_.piece;
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;

	if(current_area == Area::GATE_END){ 
		return new Transfer_PT1(data, localdata_);
	}
	return nullptr;
}

