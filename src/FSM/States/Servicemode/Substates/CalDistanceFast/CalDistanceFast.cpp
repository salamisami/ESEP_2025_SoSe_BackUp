#include "CalDistanceFast.h"


//================================================= constructors & destructors =================================================
CalDistanceFast::CalDistanceFast(ContextData* data) : OrthState(data,
	std::deque<State*>({
		new IdleCDF(data),
		new LetPieceThrough(data, OPEN_GATE_FAST_DURATION)
		})
) {
	//substate = new SubState(data);
}

CalDistanceFast::~CalDistanceFast() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void CalDistanceFast::entry() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	OrthState::entry();
}

void CalDistanceFast::exit() {
	OrthState::exit();
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

//explicit exit
State* CalDistanceFast::laser_back_blocked() {
    for(auto& current_substate : substates) {
        State* newSubstate = current_substate->laser_back_blocked();
        if(newSubstate != nullptr) {
            return newSubstate;
        }
    }
    return nullptr;
}