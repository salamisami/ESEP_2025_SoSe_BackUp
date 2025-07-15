#include "StartingAreaBlocked.h"

//================================================= constructors & destructors
//=================================================
StartingAreaBlocked::StartingAreaBlocked(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

StartingAreaBlocked::~StartingAreaBlocked() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void StartingAreaBlocked::entry() {
  PRINT_STATE;

  data->sender->send_event((int8_t)Topic::ACTUATOR,
                           (int)ActuatorEnum::LED_Q2_OFF);
  // data->timer->start_timer(2000,TIMER_ID::STARTING_AREA_TIMER);
}

void StartingAreaBlocked::exit() { PRINT_STATE; }

State *StartingAreaBlocked::unblock_starting_area() {
  return new StartingAreaUnblocked(data);
}

State *StartingAreaBlocked::laser_front_blocked() {
  return new PiecesTooClose(data);
}

// State* StartingAreaBlocked::timer(TIMER_ID id) {
//     if(id == TIMER_ID::STARTING_AREA_TIMER) {
//         return new StartingAreaUnblocked(data);
//     }
//     return nullptr;
// }

State *StartingAreaBlocked::clone() { return new StartingAreaBlocked(data); }
