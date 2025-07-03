#include "PieceControllerFBM1.h"

//================================================= constructors & destructors =================================================
PieceControllerFBM1::PieceControllerFBM1(ContextData* data) : OrthState(data,
	{}
) {
	//substate = new SubState(data);
}

PieceControllerFBM1::PieceControllerFBM1(ContextData* data, std::deque<State*> substates) :OrthState(data, substates) {}

PieceControllerFBM1::~PieceControllerFBM1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceControllerFBM1::entry() {
	PRINT_STATE;
}

void PieceControllerFBM1::exit() {
	PRINT_STATE;
}

State* PieceControllerFBM1::clone() {
	return new PieceControllerFBM1(data);
}

State* PieceControllerFBM1::new_piece() {
	int id = data->available_id;
	data->available_id++;

	//add new piece entry to shared data
	Piece* next_piece = new Piece(id);
	data->pieces_map->insert({ id, next_piece });

	//create a local data and inject the id
	LocalDataPT1 localdata;
	localdata.id = id;
	spawn_orthogonal_state(new Start_PT1(data, localdata));

	return nullptr;
}

//TODO check if the event is consumed or not here
State* PieceControllerFBM1::laser_back_blocked() {
	for(auto it = substates.begin(); it != substates.end();) {
		State* current_substate = *it;
		// if(current_substate == nullptr) {
		// 	DEBUG("this substate is nullptr");
		// 	return nullptr;
		// }

		State* newSubstate = current_substate->laser_back_blocked();
		if(newSubstate == State::EXIT_STATE) {
			//TODO despawn the state
			// Handle substate exit
			current_substate->exit();
			delete current_substate;
			current_substate = nullptr;
			it = substates.erase(it);
			//TODO event is consumed, result is exit state
			return nullptr;
		} else if(newSubstate != nullptr) {
			// there is substate change, change only the substate
			current_substate->exit();
			delete current_substate;
			current_substate = newSubstate;
			current_substate->entry();
			//TODO event is consumed, result is substate change
		}
		//event is not consumed
		return nullptr;
	}
	return nullptr;
}

State* PieceControllerFBM1::metal_detected() {

}

State* PieceControllerFBM1::laser_sorting_gate_blocked() {

}