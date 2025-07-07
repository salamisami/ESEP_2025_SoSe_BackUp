#include "SortingOut_PT1.h"

//================================================= constructors & destructors =================================================
SortingOut_PT1::SortingOut_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
  //substate = new SubState(data);
}

SortingOut_PT1::~SortingOut_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SortingOut_PT1::entry() {
  data->timer->start_timer(1000, TIMER_ID::SORTINGOUT_PT1);
  data->stopwatch.start();
  PRINT_STATE;
}

void SortingOut_PT1::exit() {
  data->stopwatch.stop();
  PRINT_STATE;
}

State* SortingOut_PT1::clone() {
  return new SortingOut_PT1(data, localdata_);
}

State* SortingOut_PT1::laser_ramp_blocked() {
  data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.id);
  Piece* piece_to_delete = data->pieces_map->at(localdata_.id);
	data->pieces_map->erase(localdata_.id);
	delete piece_to_delete;
  return State::EXIT_STATE;
}

State* SortingOut_PT1::timer(TIMER_ID id) {
  if(id == TIMER_ID::SORTINGOUT_PT1) {
    DEBUG("PieceMissing! Cause: piece is too long to reach ramp.");
    data->sender->send_event((int8_t) Topic::ERROR, (int) Error_Enum::ERROR_W_LOST);
    data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.id);
    PieceEnum validated_piece = localdata_.validated_type;
    switch(validated_piece) {
      case PieceEnum::FLAT:
        data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_FLAT);
        break;
      case PieceEnum::TALL:
        data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL);
        break;
      case PieceEnum::TALL_WITH_METAL:
        data->sender->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::RESET_TO_TALL_W_METAL);
        break;
      default:
        break;
    }
    Piece* piece_to_delete = data->pieces_map->at(localdata_.id);
    data->pieces_map->erase(localdata_.id);
    delete piece_to_delete;
    return State::EXIT_STATE;
  }
  return nullptr;
}

