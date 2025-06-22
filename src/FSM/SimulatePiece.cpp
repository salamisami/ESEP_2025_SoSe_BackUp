#include "SimulatePiece.h"

//================================================= constructors & destructors =================================================
SimulatePiece::SimulatePiece(ContextData* data) : OrthState(data, std::vector<State*>({
	new Fast(data),
	new LetPieceThrough(data, OPEN_GATE_FAST_DURATION)
})) {
    //substate = new SubState(data);
}

SimulatePiece::~SimulatePiece() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SimulatePiece::entry(){
	PRINT_STATE;

	//Anlage 11
	// TimeProfile fast_profile = { { 2084, 2459, 3473, 3955, 5741, 3699 } };
	// TimeProfile slow_profile = { { 6060, 7183, 10309, 11780, 17207, 10552 } };

	TimeProfile fast_profile = { { 2000, 2100, 3600, 4000, 6000, 3800 } };
	TimeProfile slow_profile = { { 6060, 7183, 10309, 11780, 17207, 10552 } };
	data->piece = new Piece(slow_profile, fast_profile, 100);
	data->piece->fast();
	OrthState::entry();
}

void SimulatePiece::exit(){
	OrthState::exit();
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	std::cout << "Area: " << (int) data->piece->getArea() << ", " << "Position: " << (double) data->piece->getPosition() << std::endl;
	delete data->piece;
	PRINT_STATE;
}

State* SimulatePiece::laser_back_blocked(){
	return new IdleTest(data);
}