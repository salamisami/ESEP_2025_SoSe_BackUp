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
	OrthState::entry();
}

void PieceControllerFBM1::exit() {
	OrthState::exit();
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

State* PieceControllerFBM1::custom_handler_function(State* (State::* handler_function)()) {
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            
            State* newSubstate = (current_substate->*handler_function)();

            if(newSubstate == State::EXIT_STATE) {
				//TODO event is consumed to exit the state
                // Handle exit case
                current_substate->exit();
                delete current_substate;
                it = substates.erase(it);
				//TODO event is consumed, result is exit state
                return nullptr;
            }

            if(newSubstate != nullptr) {
				//TODO event is consumed
                // Handle state transition
                current_substate->exit();
                delete current_substate;
                current_substate = newSubstate;
                current_substate->entry();
            }

            ++it;  // Common increment for both remaining cases
        }
		//TODO event not consumed at all
        return nullptr;
    }

//TODO check if the event is consumed or not here
State* PieceControllerFBM1::laser_back_blocked() {
	return custom_handler_function(&State::laser_back_blocked);
}

State* PieceControllerFBM1::metal_detected() {
	return custom_handler_function(&State::metal_detected);

}

State* PieceControllerFBM1::laser_sorting_gate_blocked() {
	return custom_handler_function(&State::laser_sorting_gate_blocked);
}