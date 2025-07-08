#include "Operating.h"

//================================================= constructors & destructors =================================================
#ifdef FBM_1
Operating::Operating(ContextData* data) : OrthState(data, {
	new PieceControllerFBM1(data),
	new MotorControl(data),
	new SortingOrder(data),
	new StartingAreaTracker(data),
	new IdleSorting(data),
	new RampNotFull(data), //Ramp Status
	new NoRampFull(data) //system ramp status
	}) {
}
#else
#ifdef FBM_2
Operating::Operating(ContextData* data) : OrthState(data, {
	new ReadyForPiece(data),
	new MotorControl(data),
	new RampNotFull(data), //Ramp Status
	new NoRampFull(data) //system ramp status
	}) {
}
#endif
#endif

Operating::Operating(ContextData* data, std::deque<State*> initial_substates) : OrthState(data, initial_substates) {
}
Operating::~Operating() {
}

//===================================================== private functions =====================================================

//void Operating::privateFunction(){}

//===================================================== public functions =====================================================

void Operating::entry() {
	PRINT_STATE;

	data->sender->send_event((int8_t) Topic::ACTUATOR,
		(int) ActuatorEnum::TRAFFIC_GREEN_ON);
	OrthState::entry();
}

void Operating::exit() {
	OrthState::entry();
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR,
		(int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Operating::clone() {
	return new Operating(data, OrthState::clone_substates());
}

State* Operating::button_stop_pressed() {
	if(data->no_error_or_warning) {
		//save history
		data->operating_history->push(this->clone());
		return new IdleIM(data);
	}
	return nullptr;
}
