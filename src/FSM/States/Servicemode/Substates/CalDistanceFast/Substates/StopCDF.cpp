#include "StopCDF.h"

//================================================= constructors & destructors =================================================
StopCDF::StopCDF(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StopCDF::~StopCDF() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StopCDF::entry(){
	PRINT_STATE;
    long total_fast_travel_time = data->stopwatch.stop();
	std::cout << "Total Fast Travel Time: " << (float) total_fast_travel_time/1000 << std::endl;
	//TODO save the time to a file
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
}

void StopCDF::exit(){
    PRINT_STATE;
}