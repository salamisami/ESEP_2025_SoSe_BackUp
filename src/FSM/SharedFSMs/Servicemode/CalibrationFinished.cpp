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
	for(auto& current : data->timeprofile.fast_timestamps){
		std::cout << "Timestamp fast: " << current << std::endl;
	}

	for(auto& current : data->timeprofile.slow_timestamps){
		std::cout << "Timestamp slow: " << current << std::endl;
	}
	TimeProfileManager::save_profile(data->timeprofile, SAVE_LOCATION_TIMEPROFILE);
	TimeProfileManager::convert_to_deadlines(&data->timeprofile);
}

void CalibrationFinished::exit(){
	PRINT_STATE;
}