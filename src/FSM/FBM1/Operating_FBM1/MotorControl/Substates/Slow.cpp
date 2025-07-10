#include "Slow.h"

//================================================= constructors & destructors =================================================
Slow::Slow(ContextData *data) : State(data)
{
  // substate = new SubState(data);
}

Slow::~Slow() {}

//===================================================== private functions =====================================================

//===================================================== public functions =====================================================
void Slow::entry()
{
  MotorControl::updateData(data, MotorPieceState::SLOW);
  data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::MOTOR_SLOW_ON, (int)EventPriority::SECOND_PRIO);
  data->sender->send_event((int8_t)Topic::ACTUATOR, (int)ActuatorEnum::MOTOR_RIGHT_START, (int)EventPriority::SECOND_PRIO);
  PRINT_STATE;
}

void Slow::exit()
{
  PRINT_STATE;
}

State *Slow::motor_fast()
{
  if (data->motor_slowed)
  {
    return new Slow(data);
  }
  else
  {
    return new Fast(data);
  }
}

State *Slow::motor_stop_fsm()
{
  return new Stop(data);
}

State *Slow::delete_w_motor()
{
  MotorControl::updateData(data, MotorPieceState::DELETE_W_MOTOR);
  if (data->workpieces)
  {
    return new Slow(data);
  }
  else
  {
    return new Idle(data);
  }
}

State *Slow::motor_slow()
{
  return new Slow(data);
}

State *Slow::clone()
{
  return new Slow(data);
}
