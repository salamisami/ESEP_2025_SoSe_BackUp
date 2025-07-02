#include "ErrorHandler.h"


//================================================= constructors & destructors =================================================
ErrorHandler::ErrorHandler(ContextData* data) : OrthState(data,
	{
		//TODO return substate...
	}
) {
	//substate = new SubState(data);
}

ErrorHandler::~ErrorHandler() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
State* ErrorHandler::clone()
{
	auto cloned_substates = OrthState::clone_substates();
	ErrorHandler* cloned_state = new ErrorHandler(data, clone_substates);
	return cloned_state;
}

void ErrorHandler::entry() {
	PRINT_STATE;
	//data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	OrthState::entry();
}

void ErrorHandler::exit() {
	OrthState::exit();
	PRINT_STATE;
	//data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	//data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

//explicit exit
/* State* ErrorHandler::laser_back_blocked() {
    for(auto& current_substate : substates) {
        State* newSubstate = current_substate->laser_back_blocked();
        if(newSubstate != nullptr) {
            return newSubstate;
        }
    }
    return nullptr;
} */