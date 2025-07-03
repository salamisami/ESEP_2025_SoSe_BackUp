#include "PieceMissing_PT1.h"

//================================================= constructors & destructors =================================================
PieceMissing_PT1::PieceMissing_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
  //substate = new SubState(data);
}

PieceMissing_PT1::~PieceMissing_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void PieceMissing_PT1::entry() {
  PRINT_STATE;
  data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_LOST);
  data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.id);
  
  if(localdata_.ist_type == ScannedPiece::FLAT) {
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_FLAT);
  } else if(localdata_.ist_type == ScannedPiece::TALL) {
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL);
  } else if(localdata_.is_metal) {
    data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL_W_METAL);
  }
  
  // State::EXIT_STATE;
}

void PieceMissing_PT1::exit() {
  PRINT_STATE;
}

State* PieceMissing_PT1::clone() {
  return new PieceMissing_PT1(data, localdata_);
}

