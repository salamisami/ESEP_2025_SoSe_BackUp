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
	TimeProfileManager::save_profile(data->timeprofile_fast, data->timeprofile_slow, SAVE_LOCATION);
}

void CalibrationFinished::exit(){
	PRINT_STATE;
}