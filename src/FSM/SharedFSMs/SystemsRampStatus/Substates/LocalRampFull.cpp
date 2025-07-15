#include "LocalRampFull.h"

//================================================= constructors & destructors
//=================================================
LocalRampFull::LocalRampFull(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

LocalRampFull::~LocalRampFull() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void LocalRampFull::entry() { PRINT_STATE; }

void LocalRampFull::exit() { PRINT_STATE; }

State *LocalRampFull::com_ramp_full() {
  data->is_ramp_full_com = true;
  return new BothRampsFull(data);
}

State *LocalRampFull::ramp_not_full() {
  data->is_ramp_full_local = false;
  return new NoRampFull(data);
}

State *LocalRampFull::clone() { return new LocalRampFull(data); }
