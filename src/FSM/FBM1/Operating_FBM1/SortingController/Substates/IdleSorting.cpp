#include "IdleSorting.h"

//================================================= constructors & destructors =================================================
IdleSorting::IdleSorting(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

IdleSorting::~IdleSorting() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void IdleSorting::entry(){	
	PRINT_STATE;
}

void IdleSorting::exit(){
    PRINT_STATE;
}

State* IdleSorting::clone() {
    return new IdleSorting(data);
}

State* IdleSorting::sort_out(){
  if (!data->is_switch){
    return new PushRamp_OP(data);
  }
  return nullptr;
}

State* IdleSorting::let_through(){
  if (data->is_switch){
    return new OpenGate_OP(data);
  }
  return nullptr;
}
