#include "Operating.h"

//================================================= constructors & destructors =================================================
#ifdef FBM_1
Operating::Operating(ContextData* data) : OrthState(data, {
	new PieceControllerFBM1(data),
	new MotorControl(data),
	new StartingAreaTracker(data),
	new IdleSorting(data)
	}) {
}
#else
#ifdef FBM_2
Operating::Operating(ContextData* data) : OrthState(data,
	{
		new ReadyForPiece(data),
		new MotorControl(data),
		new IdleSorting(data)
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
	OrthState::exit();
	PRINT_STATE;
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_RED_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_Q1_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_Q2_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_RESET_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::LED_START_OFF);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	// data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

State* Operating::clone() {
	return new Operating(data, OrthState::clone_substates());
}

State* Operating::button_stop_pressed() {
	if(!data->error_warning_counter->is_error_or_warning()){
		data->operating_history->push(this->clone());
		return new IdleIM(data);
	}
	return nullptr;
}
