#include "Calibrating.h"

//================================================= contructors & destructors =================================================
Calibrating::Calibrating(ContextData* data) : State(data){}

Calibrating::~Calibrating() {}

//===================================================== private functions =====================================================

//void Calibrating::privateFunction(){}

//===================================================== public functions =====================================================

void Calibrating::entry(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
    data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATE);
}

void Calibrating::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

State* Calibrating::adc_calibration_done(){
    return new CalibrationDone(data);
}