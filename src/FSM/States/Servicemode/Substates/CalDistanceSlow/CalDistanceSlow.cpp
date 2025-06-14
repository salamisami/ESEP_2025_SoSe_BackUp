#include "CalDistanceSlow.h"

//================================================= constructors & destructors =================================================
CalDistanceSlow::CalDistanceSlow(ContextData* data) : OrthogonalState(data,
	std::vector<I_State*>({
		new IdleCDS(data),
		new IdleGateCDS(data)
		})
) {
	//substate = new SubState(data);
}

CalDistanceSlow::~CalDistanceSlow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalDistanceSlow::entry() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	OrthogonalState::entry();
}

void CalDistanceSlow::exit() {
	OrthogonalState::exit();
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
}