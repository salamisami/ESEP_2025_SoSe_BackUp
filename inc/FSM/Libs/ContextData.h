#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#pragma once

#include "ErrorWarningCounter.h"
#include "QNet.h"
#include "StateContainer.h"
// #include "State.h"
#include "DistanceTracker.h"
#include "Piece.h"
#include "Stopwatch.h"
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

// forward declaration
class State;

class ContextData {
  //============================================ constructors & destructors
  //============================================
public:
  /**
   * @brief Creates a context data by injecting the sender interface
   * @param sender to send events out
   */
  ContextData(I_Sender *sender);
  ContextData();
  virtual ~ContextData();

  //================================================ public functions
  //================================================
public:
  //================================================ private variables
  //================================================
public:
  int event_payload;
  Stopwatch stopwatch;
  TimeProfile timeprofile;
  DistanceTracker *piece_tracker = nullptr; // = DistanceTracker(true);
  std::stack<State *> *operating_history;
  std::stack<State *> *modehandler_history;
  std::stack<State *> *estop_history;

    std::unordered_map<int, Piece*>* pieces_map;
    int available_id = 1;
    Piece* piece_FBM2_soll = nullptr;
    //Piece* piece_FBM2_ist = nullptr;

  ScannedPiece scanned_piece_FBM2 = ScannedPiece::UNKNOWN;
  bool scanned_piece_has_metal_fbm2 = false;

  // int piece_id = 0;
  // PieceEnum ist_type = PieceEnum::UNKNOWN;
  // PieceEnum soll_type = PieceEnum::UNKNOWN;
  // long sorting_time = 0;
  // DistanceTracker* piece_tracker;
  long sort_out_time = 0;

  I_Sender *timer_sender;
  Timer *timer;
  I_Sender *sender;

  bool is_ramp_full = false;

  bool workpieces = false;
  bool motor_slowed = false;
  bool motor_stopped = false;
  int8_t motorpieceRequest = -1;

  StateContainer workpieceList;
  MotorPieceState current_motor_speed = MotorPieceState::STOPPED;

  bool is_estop = false;
  bool config = false;
  bool com_resolved = true;
  bool mqtt_resolved = true;
  ErrorWarningCounter *error_warning_counter;

  // PieceTrack -> PieceTrack
  int piece_near_adc = 0;
};

#endif
