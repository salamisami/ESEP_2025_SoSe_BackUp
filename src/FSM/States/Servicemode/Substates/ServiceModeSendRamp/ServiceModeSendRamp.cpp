#include "ServiceModeSendRamp.h"

//================================================= contructors & destructors =================================================
ServiceModeSendRamp::ServiceModeSendRamp(ContextData* data) : OrthogonalState(data,
	std::vector<I_State*>({
		new IdleSMSR(data),
		new IdleGateCP(data)
		})
) {
	//substate = new SubState(data);
}

ServiceModeSendRamp::~ServiceModeSendRamp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ServiceModeSendRamp::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATE);
}

void ServiceModeSendRamp::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}