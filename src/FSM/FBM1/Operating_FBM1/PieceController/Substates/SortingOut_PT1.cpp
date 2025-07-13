#include "SortingOut_PT1.h"

//================================================= constructors & destructors =================================================
SortingOut_PT1::SortingOut_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
  //substate = new SubState(data);
}

SortingOut_PT1::~SortingOut_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SortingOut_PT1::entry() {
  PRINT_STATE;
  data->timer->start_timer(SORT_OUT_TIME, TIMER_ID::SORTINGOUT_PT1);
  data->stopwatch.reset();
  data->stopwatch.start();
}

void SortingOut_PT1::exit() {
  PRINT_STATE;
}

State* SortingOut_PT1::clone() {
  return new SortingOut_PT1(data, localdata_);
}

State* SortingOut_PT1::laser_ramp_blocked() {
  data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.piece->id);
  Piece* piece = localdata_.piece;

  piece->sorting_time = data->stopwatch.stop();
  printf("Piece ID: %d has sorting time of %ld ms\n", piece->id, piece->sorting_time);

  data->pieces_map->erase(localdata_.piece->id);
  delete piece;
  return State::EXIT_STATE;
}

State* SortingOut_PT1::timer(TIMER_ID id) {
  if(id == TIMER_ID::SORTINGOUT_PT1) {
    DEBUG("PieceMissing! Cause: piece is too long to reach ramp.");
    MACRO_PIECE_MISSING_PT1
  }
  return nullptr;
}

