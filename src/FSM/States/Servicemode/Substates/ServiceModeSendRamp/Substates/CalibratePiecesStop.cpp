#include "CalibratePiecesStop.h"

//================================================= contructors & destructors =================================================
CalibratePiecesStop::CalibratePiecesStop(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

CalibratePiecesStop::~CalibratePiecesStop() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalibratePiecesStop::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
    std::cout << "Please put a piece" << std::endl;
}

void CalibratePiecesStop::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

I_State* CalibratePiecesStop::laser_front_blocked(){
    return new CalDistanceFast(data);
}