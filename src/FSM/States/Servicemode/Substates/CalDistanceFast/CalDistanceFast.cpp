#include "CalDistanceFast.h"

//================================================= contructors & destructors =================================================
CalDistanceFast::CalDistanceFast(ContextData* data) : OrthogonalState(data,
	std::vector<I_State*>({
		new IdleCDF(data),
		new IdleGateCDF(data)
		})
) {
	//substate = new SubState(data);
}

CalDistanceFast::~CalDistanceFast() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalDistanceFast::entry(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
}

void CalDistanceFast::exit(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}