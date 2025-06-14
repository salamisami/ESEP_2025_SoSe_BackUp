#include "StopCDS.h"

//================================================= constructors & destructors =================================================
StopCDS::StopCDS(ContextData* data) : HState(data) {
    //substate = new SubState(data);
}

StopCDS::~StopCDS() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StopCDS::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	long total_slow_travel_time = data->stopwatch.stop();
	std::cout << "Total Slow Travel Time: " << (float) total_slow_travel_time/1000 << std::endl;
	//TODO save the time to a file

	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
}

void StopCDS::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}