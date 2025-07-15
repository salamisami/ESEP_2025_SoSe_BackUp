#include "ComRampFull.h"

//================================================= constructors & destructors
//=================================================
ComRampFull::ComRampFull(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

ComRampFull::~ComRampFull() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void ComRampFull::entry() {
  // data->sender->send_event((int8_t) Topic::ACTUATOR, (int)
  // ActuatorEnum::TRAFFIC_YELLOW_ON_FAST);
  PRINT_STATE;
}

void ComRampFull::exit() { PRINT_STATE; }

State *ComRampFull::com_ramp_not_full() {
  data->is_ramp_full_com = false;
  return new NoRampFull(data);
}

State *ComRampFull::ramp_full() {
  data->is_ramp_full_local = true;
  return new BothRampsFull(data);
}

State *ComRampFull::clone() { return new ComRampFull(data); }
