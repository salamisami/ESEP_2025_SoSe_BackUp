#include "Idle.h"

//================================================= constructors & destructors =================================================
Idle::Idle(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Idle::~Idle() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Idle::entry(){
  if (data->event_topic != (int8_t) Topic::DELETE_W_MOTOR ){
    MotorControl::updateData(data, MotorPieceState::STOPPED);
  }
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP, (int) EventPriority::SECOND_PRIO);
	data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::MOTOR_SLOW_OFF, (int)EventPriority::SECOND_PRIO);
    PRINT_STATE;
}

void Idle::exit(){
    PRINT_STATE;
}

State* Idle::motor_fast(){
    return new Fast(data);
}

State *Idle::motor_stop_fsm()
{
  return new Stop(data);
}

State* Idle::clone() {
    return new Idle(data);
}
