#include "PieceControllerFBM1.h"

//================================================= constructors & destructors =================================================
PieceControllerFBM1::PieceControllerFBM1(ContextData* data) : OrthState(data,
	{}
	, nullptr
	, false
	, false
) {
	//substate = new SubState(data);
}

PieceControllerFBM1::PieceControllerFBM1(ContextData* data, std::deque<State*> substates) :OrthState(data, substates, nullptr, false, false) {}

PieceControllerFBM1::~PieceControllerFBM1() {
}


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
	return new PieceControllerFBM1(data, clone_substates());
}

State* PieceControllerFBM1::new_piece() {
	int id = data->available_id;
	data->available_id++;

	//add new piece entry to shared data
	Piece* next_piece = new Piece(id, &data->timeprofile);
	data->pieces_map->insert({ id, next_piece });
	//create a local data and inject the id
	LocalDataPT1 localdata;
	localdata.piece = next_piece;
	spawn_orthogonal_state(new Start_PT1(data, localdata));
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) id);
	return nullptr;
}


State* PieceControllerFBM1::laser_back_blocked() {
	State* newState = handle_event_using_special_function(&State::laser_back_blocked);

	return newState;
}

State* PieceControllerFBM1::laser_sorting_gate_blocked() {
	State* newState = handle_event_using_special_function(&State::laser_sorting_gate_blocked);
	//here
	return newState;
}

State* PieceControllerFBM1::handle_event_using_special_function(State* (State::* handler_function)()) {
        if(substates.empty() && quit_on_empty_) {
            return default_exit_state_;
        }

		bool event_consumed = true;

        auto it = substates.begin();
        while(it != substates.end()) {
            State*& current_substate = *it;
            State* newSubstate = (current_substate->*handler_function)();

            if(newSubstate == State::EXIT_STATE) {
                // Handle exit case
                current_substate->exit();
                delete current_substate;
                it = substates.erase(it);
				event_consumed = true;
				break;

                // If we've removed all substates, return the exit state
                // if(substates.empty() && quit_on_empty_) {
                //     return default_exit_state_;
                // }
            } else if(newSubstate != nullptr) {
                // Handle state transition only if it's a different state
                current_substate->exit();
                delete current_substate;
                current_substate = newSubstate;
                current_substate->entry();
                ++it;
				event_consumed = true;
				break;
            } else {
				//no state change
                event_consumed = false;
                ++it;
            }
        }

		if(!event_consumed){
			data->sender->send_event((int) Topic::ERROR, (int8_t) Error_Enum::ERROR_W_APPEARED);
		}

        return nullptr;
    }