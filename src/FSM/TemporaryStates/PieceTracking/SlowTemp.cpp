#include "SlowTemp.h"

//================================================= constructors & destructors =================================================
SlowTemp::SlowTemp(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

SlowTemp::~SlowTemp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SlowTemp::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->piece_tracker->slow();

}

void SlowTemp::exit(){
	PRINT_STATE;
}

State* SlowTemp::button_reset_released(){
	return new FastTemp(data);
}

State* SlowTemp::clone() {
	return new SlowTemp(data);
}