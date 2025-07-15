#include "StartingAreaUnblocked.h"

//================================================= constructors & destructors
//=================================================
StartingAreaUnblocked::StartingAreaUnblocked(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

StartingAreaUnblocked::~StartingAreaUnblocked() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void StartingAreaUnblocked::entry() {
  PRINT_STATE;

  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::LED_Q2_ON);
}

void StartingAreaUnblocked::exit() { PRINT_STATE; }

State *StartingAreaUnblocked::laser_front_blocked() {
  data->sender->send_event((int8_t)Topic::INTERNAL,
                           (int)Internal_Enum::NEW_PIECE);
  return new StartingAreaBlocked(data);
}

State *StartingAreaUnblocked::clone() {
  return new StartingAreaUnblocked(data);
}
