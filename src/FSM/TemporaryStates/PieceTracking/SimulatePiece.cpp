#include "SimulatePiece.h"

//================================================= constructors & destructors =================================================
SimulatePiece::SimulatePiece(ContextData* data) : OrthState(data, std::deque<State*>({
	new FastTemp(data),
	new LetPieceThrough(data, OPEN_GATE_FAST_DURATION)
})) {
    //substate = new SubState(data);
}

SimulatePiece::~SimulatePiece() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SimulatePiece::entry(){
	PRINT_STATE;
	data->piece_tracker.reset();

	//Anlage 11
	// TimeProfile fast_profile = { { 2084, 2459, 3473, 3955, 5741, 3699 } };
	// TimeProfile slow_profile = { { 6060, 7183, 10309, 11780, 17207, 10552 } };

	// TimeProfile fast_profile = { { 2000, 2100, 3600, 4000, 6000, 3800 } };
	// TimeProfile slow_profile = { { 6060, 7183, 10309, 11780, 17207, 10552 } };
//	data->piece = new Piece(data->timeprofile_slow, da);
	OrthState::entry();
}

void SimulatePiece::exit(){
	OrthState::exit();
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	auto distance = data->piece_tracker.get_distance();
	std::cout << "Area: " << (int) distance.first << ", " << "Position: " << (double) distance.second << std::endl;
	//delete data->piece_tracker;
	PRINT_STATE;
}

State* SimulatePiece::laser_back_blocked(){
	return new IdleTest(data);
}