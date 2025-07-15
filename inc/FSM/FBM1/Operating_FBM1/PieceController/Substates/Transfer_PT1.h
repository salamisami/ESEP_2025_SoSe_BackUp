#ifndef TRANSFER_PT1_H
#define TRANSFER_PT1_H
#pragma once

#include "LocalDataPT1.h"
#include "Piece.h"
#include "State.h"

class Transfer_PT1 : public State {
public: //============================================ constructors &
        // destructors ============================================
  Transfer_PT1(ContextData *data, LocalDataPT1 localdata);
  virtual ~Transfer_PT1();

public: //================================================ public functions
        //================================================
  void entry() override;
  void exit() override;
  State *clone() override;

  State *transfer_done() override;
  State *transfer_failed() override;
  State *timer(TIMER_ID id) override;

private: //================================================ private variables
         //================================================
  // classes, STL containers, and structs
  // pointers
  // primitive types
  LocalDataPT1 localdata_;
  // bool and char

private
    : //================================================ private functions
      //================================================ void privateFunction();
};

#endif
