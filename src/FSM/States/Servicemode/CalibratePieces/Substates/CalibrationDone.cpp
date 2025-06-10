#include "CalibrationDone.h"

//================================================= contructors & destructors =================================================
CalibrationDone::CalibrationDone(ContextData* data):State(data) {}

CalibrationDone::~CalibrationDone() {}

//===================================================== private functions =====================================================

//void CalibrationDone::privateFunction(){}

//===================================================== public functions =====================================================

void CalibrationDone::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
}

void CalibrationDone::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}