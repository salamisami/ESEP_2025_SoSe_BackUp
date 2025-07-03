#include "CalDistanceSlow.h"


//================================================= constructors & destructors =================================================
CalDistanceSlow::CalDistanceSlow(ContextData* data) : OrthState(data,
	std::deque<State*>({
		new IdleCDS(data),
		new LetPieceThrough(data, OPEN_GATE_SLOW_DURATION)
		})
) {
	//substate = new SubState(data);
}

CalDistanceSlow::~CalDistanceSlow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalDistanceSlow::entry() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	OrthState::entry();
}

void CalDistanceSlow::exit() {
	OrthState::exit();
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
}

//explicit exit
State* CalDistanceSlow::laser_back_blocked() {
    for(auto& current_substate : substates) {
        State* newSubstate = current_substate->laser_back_blocked();
        if(newSubstate != nullptr) {
            return newSubstate;
        }
    }
    return nullptr;
}