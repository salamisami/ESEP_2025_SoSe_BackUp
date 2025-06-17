#include "PieceGoingGate.h"

//================================================= constructors & destructors =================================================
PieceGoingGate::PieceGoingGate(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

PieceGoingGate::~PieceGoingGate() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceGoingGate::entry(){
	PRINT_STATE
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_LEFT_START);
	int time_required = data->timeprofile.timestamp[(int) Timestamp::END] - data->timeprofile.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
	data->timer->start_timer(time_required + 1000, TIMER_ID::CalGateRamp1);
}

void PieceGoingGate::exit(){
	PRINT_STATE
}

State* PieceGoingGate::timer(TIMER_ID id){
	if(id == TIMER_ID::CalGateRamp1){
		return new PieceGoingGateBackward(data);
	}
	return nullptr;
}