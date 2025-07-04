#include "FastTemp.h"

//================================================= constructors & destructors =================================================
FastTemp::FastTemp(ContextData *data) : State(data)
{
	// substate = new SubState(data);
}

FastTemp::~FastTemp() {}

//===================================================== private functions =====================================================

//===================================================== public functions =====================================================
void Fast::entry(){
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
	data->piece_tracker.fast();
	PRINT_STATE;
}

void FastTemp::exit()
{
	PRINT_STATE;
}

State *FastTemp::button_reset_pressed()
{
	return new Slow(data);
}