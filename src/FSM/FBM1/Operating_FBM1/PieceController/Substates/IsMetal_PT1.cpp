#include "IsMetal_PT1.h"

//================================================= constructors & destructors =================================================
IsMetal_PT1::IsMetal_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

IsMetal_PT1::~IsMetal_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IsMetal_PT1::entry(){
	PRINT_STATE;
	localdata_.is_metal = true;
}

void IsMetal_PT1::exit(){
	PRINT_STATE;
}

State* IsMetal_PT1::clone(){
	return new IsMetal_PT1(data, localdata_);
}

State* IsMetal_PT1::laser_sorting_gate_blocked() {
	auto piece = data->pieces_map->at(localdata_.id);
	auto distance = piece->piece_tracker->get_distance();
	Area current_area = distance.first;

	if(current_area == Area::GATE){
		return new Gate_PT1(data, localdata_);
	}

	return nullptr;
}