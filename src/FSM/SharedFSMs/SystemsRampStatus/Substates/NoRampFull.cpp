#include "NoRampFull.h"

//================================================= constructors & destructors
//=================================================
NoRampFull::NoRampFull(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

NoRampFull::~NoRampFull() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void NoRampFull::entry() { PRINT_STATE; }

void NoRampFull::exit() { PRINT_STATE; }

State *NoRampFull::ramp_full() {
  data->is_ramp_full_local = true;
  return new LocalRampFull(data);
}

State *NoRampFull::com_ramp_full() {
  data->is_ramp_full_com = true;
  return new ComRampFull(data);
}

State *NoRampFull::clone() { return new NoRampFull(data); }
