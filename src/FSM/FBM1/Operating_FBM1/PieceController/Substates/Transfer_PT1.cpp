#include "Transfer_PT1.h"

//================================================= constructors & destructors
//=================================================
Transfer_PT1::Transfer_PT1(ContextData *data, LocalDataPT1 localdata)
    : State(data), localdata_(localdata) {
  // substate = new SubState(data);
}

Transfer_PT1::~Transfer_PT1() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void Transfer_PT1::entry() {
  data->timer->start_timer(3000, TIMER_ID::TRANSFER_PT1);
  PRINT_STATE;
}

void Transfer_PT1::exit() { PRINT_STATE; }

State *Transfer_PT1::clone() { return new Transfer_PT1(data, localdata_); }

State *Transfer_PT1::transfer_done() {
  data->sender->send_event((int8_t)Topic::DELETE_W_MOTOR,
                           (int)localdata_.piece->id);
  Piece *piece_to_delete = localdata_.piece;

  data->pieces_map->erase(localdata_.piece->id);
  delete piece_to_delete;
  return State::EXIT_STATE;
}

State *Transfer_PT1::timer(TIMER_ID id) {
  if (id == TIMER_ID::TRANSFER_PT1) {
    MACRO_PIECE_MISSING_PT1
  }
  return nullptr;
}

State *Transfer_PT1::transfer_failed() {
  DEBUG("PieceMissing! Cause: piece does not reach to FBM2.");
  printf("Error: Piece did not reach FBM2.\n");
  MACRO_PIECE_MISSING_PT1
}
