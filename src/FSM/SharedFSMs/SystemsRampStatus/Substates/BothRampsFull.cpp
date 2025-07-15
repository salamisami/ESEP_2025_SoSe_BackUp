#include "BothRampsFull.h"

//================================================= constructors & destructors
//=================================================
BothRampsFull::BothRampsFull(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

BothRampsFull::~BothRampsFull() {}

//===================================================== private functions
//=====================================================


//===================================================== public functions =====================================================
void BothRampsFull::entry(){
	PRINT_STATE;
    
}

void BothRampsFull::exit() { PRINT_STATE; }

State *BothRampsFull::com_ramp_not_full() {
  data->is_ramp_full_com = false;
  return new LocalRampFull(data);
}

State *BothRampsFull::ramp_not_full() {
  data->is_ramp_full_local = false;
  return new ComRampFull(data);
}


State* BothRampsFull::sort_out()
{
	data->sender->send_event((int8_t)Topic::ERROR, (int) Error_Enum::ERROR_BOTH_R_FULL);
    return new BothRampsFull(data);
}


State *BothRampsFull::clone() { return new BothRampsFull(data); }
