#include "PieceTallWithMetal.h"

//================================================= constructors & destructors
//=================================================
PieceTallWithMetal::PieceTallWithMetal(ContextData *data) : State(data) {
  // substate = new SubState(data);
}

PieceTallWithMetal::~PieceTallWithMetal() {}

//===================================================== private functions
//=====================================================

//===================================================== public functions
//=====================================================
void PieceTallWithMetal::entry() {
  PRINT_STATE;
  std::cout << "Current Sortingorder: Tall Piece with hole and metal"
            << std::endl;
}

void PieceTallWithMetal::exit() { PRINT_STATE; }

State *PieceTallWithMetal::clone() { return new PieceTallWithMetal(data); }

State *PieceTallWithMetal::reset_to_flat() { return new PieceFlat(data); }

State *PieceTallWithMetal::reset_to_tall() { return new PieceTall(data); }

State *PieceTallWithMetal::com_reset_to_flat() { return new PieceFlat(data); }

State *PieceTallWithMetal::com_reset_to_tall() { return new PieceTall(data); }

State *PieceTallWithMetal::tall_w_metal_piece() {
  data->sender->send_event((int8_t)Topic::INTERNAL,
                           (int)Internal_Enum::LET_THROUGH);
  return new PieceFlat(data);
}

State *PieceTallWithMetal::flat_piece() {
  if (data->is_ramp_full_local) {
    data->sender->send_event((int8_t)Topic::INTERNAL,
                             (int)Internal_Enum::SORT_OUT_FBM2);
  } else {
    data->sender->send_event((int8_t)Topic::INTERNAL,
                             (int)Internal_Enum::SORT_OUT);
  }
  return nullptr;
  // return new PieceTallWithMetal(data);
}

State *PieceTallWithMetal::tall_piece() {
  if (data->is_ramp_full_local) {
    data->sender->send_event((int8_t)Topic::INTERNAL,
                             (int)Internal_Enum::SORT_OUT_FBM2);
  } else {
    data->sender->send_event((int8_t)Topic::INTERNAL,
                             (int)Internal_Enum::SORT_OUT);
  }
  return nullptr;
  // return new PieceTallWithMetal(data);
}

State *PieceTallWithMetal::unknown_piece() {
  if (data->is_ramp_full_local) {
    data->sender->send_event((int8_t)Topic::INTERNAL,
                             (int)Internal_Enum::SORT_OUT_FBM2);
  } else {
    data->sender->send_event((int8_t)Topic::INTERNAL,
                             (int)Internal_Enum::SORT_OUT);
  }
  return nullptr;
  // return new PieceTallWithMetal(data);
}
