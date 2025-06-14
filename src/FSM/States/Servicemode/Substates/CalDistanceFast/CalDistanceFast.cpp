#include "CalDistanceFast.h"

//================================================= constructors & destructors =================================================
CalDistanceFast::CalDistanceFast(ContextData* data) : OrthState(data,
	std::vector<State*>({
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
	OrthState::entry();
}

void CalDistanceFast::exit(){
	OrthState::exit();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* CalDistanceFast::laser_back_unblocked(){
	return new ReadyForCDS(data);
}