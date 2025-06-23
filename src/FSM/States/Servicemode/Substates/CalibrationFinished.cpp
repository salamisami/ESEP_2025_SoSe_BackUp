#include "CalibrationFinished.h"

//================================================= constructors & destructors =================================================
CalibrationFinished::CalibrationFinished(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibrationFinished::~CalibrationFinished() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibrationFinished::entry(){
	PRINT_STATE;
	for(auto& current : data->timeprofile_fast.timestamp){
		std::cout << "Timestamp fast: " << current << std::endl;
	}

	for(auto& current : data->timeprofile_slow.timestamp){
		std::cout << "Timestamp slow: " << current << std::endl;
	}

	data->piece = new Piece(data->timeprofile_slow, data->timeprofile_fast);
}

void CalibrationFinished::exit(){
	PRINT_STATE;
}