#include "Operating.h"

//================================================= constructors & destructors =================================================
#ifdef FBM1
Operating::Operating(ContextData* data): OrthState(data, {new PseudoState(data)}) {
}
#else
#ifdef FBM2
Operating::Operating(ContextData* data): OrthState(data, {new PseudoState(data)}) {
}

#else
Operating::Operating(ContextData* data) : OrthState(data, {new PseudoState(data)}){
}
#endif
#endif

Operating::Operating(ContextData* data, std::vector<State*> initial_substates) : OrthState(data, initial_substates){
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
}

void Operating::exit() {
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR,
			(int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Operating::button_stop_pressed() {
	if (data->no_error_or_warning) {
		return new IdleIM(data);
	}
	return nullptr;
}
