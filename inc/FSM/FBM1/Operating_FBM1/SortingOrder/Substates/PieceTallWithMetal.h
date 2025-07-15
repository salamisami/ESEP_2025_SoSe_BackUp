#ifndef PIECETALLWITHMETAL_H
#define PIECETALLWITHMETAL_H
#pragma once

#include "PieceFlat.h"
#include "PieceTall.h"
#include "State.h"

class PieceTallWithMetal : public State {
public: //============================================ constructors &
        //destructors ============================================
  PieceTallWithMetal(ContextData *data);
  virtual ~PieceTallWithMetal();

public: //================================================ public functions
        //================================================
  void entry() override;
  void exit() override;
  State *clone() override;

  State *tall_w_metal_piece() override;
  State *tall_piece() override;
  State *flat_piece() override;
  State *unknown_piece() override;

  State *reset_to_flat() override;
  State *reset_to_tall() override;

  State *com_reset_to_flat() override;
  State *com_reset_to_tall() override;

private: //================================================ private variables
         //================================================ classes, STL
         // containers, and structs pointers primitive types bool and char
private
    : //================================================ private functions
      //================================================ void privateFunction();
};

#endif
