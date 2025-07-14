#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#pragma once
#include "HState.h"
#include "Idle.h"
#include <stdbool.h>

class MotorControl : public HState {
public: //============================================ constructors &
        // destructors ============================================
  MotorControl(ContextData *data);
  MotorControl(ContextData *data, State *initial_substate);
  virtual ~MotorControl();

public: //================================================ public functions
        //================================================
  void entry() override;
  void exit() override;
  State *clone() override;
  static bool slowed(ContextData *data, MotorPieceState pieceRequest) {
    return data->motor_slowed || pieceRequest == MotorPieceState::SLOW;
  }

  static bool stopped(ContextData *data, MotorPieceState pieceRequest) {
    return data->motor_stopped || pieceRequest == MotorPieceState::STOPPED;
  }

  static int motorTransition(ContextData *data, MotorPieceState pieceRequest) {
    if (stopped(data, pieceRequest)) {
      return (int)MotorPieceState::STOPPED;
    }
    if (slowed(data, pieceRequest)) {
      return (int)MotorPieceState::SLOW;
    }
    return (int)MotorPieceState::FAST;
  }

  static void updateData(
      ContextData *data,
      MotorPieceState motorPieceRequest) { // Goals: 1.Set the workpiece to the
                                           // 2nd requirement
                                           // 2. Set MotorSlowed/MotorStopped if
                                           // any of the workpieces request it
    int id = data->event_payload;
    int8_t topic = data->event_topic;
    motorPieceRequest = TOPIC_TO_MOTOR_STATE(topic);
    if (topic > (int8_t)Topic::DELETE_W_MOTOR ||
        topic < (int8_t)Topic::MOTOR_STOP_FSM) {
      return; // Topics größer als DELETE_W_MOTOR
              // sind keine Motortopics; Topics kleiner
              // als MotorStop sind auch keine Motortopics
    }
    if (topic == (int8_t)Topic::DELETE_W_MOTOR) {
      // Remove the ID from the list if it exists
      if (data->workpieceList.contains(id)) {
        data->workpieceList.remove(id);
        data->workpieceList.updateDataMotorFlags(
            data->workpieceList, data->motor_stopped, data->motor_slowed,
            MotorPieceState::DELETE_W_MOTOR, id);
        data->workpieces = !data->workpieceList.isEmpty();
      } else {
        throw("ID doesn't exist in workpiece list\n");
      }
    } else {
      // Request =/= speed
      if (!data->workpieceList.contains(id)) {
        data->workpieceList.add(id, motorPieceRequest);
      }
      data->workpieceList.updateState(id, motorPieceRequest);

      data->workpieceList.updateDataMotorFlags(
          data->workpieceList, data->motor_stopped, data->motor_slowed,
          motorPieceRequest, id);

      if (data->motor_stopped) {
        data->current_motor_speed = MotorPieceState::STOPPED;
      } else if (data->motor_slowed) {
        data->current_motor_speed = MotorPieceState::SLOW;
      } else {
        data->current_motor_speed = MotorPieceState::FAST;
      }
      for (auto &pair : *data->pieces_map) {
        Piece *piece = pair.second; // pair.second is the value (Piece*)

        // Switch case for motor states
        switch (data->current_motor_speed) {
        case MotorPieceState::FAST:
          piece->piece_tracker->fast();
          break;
        case MotorPieceState::SLOW:
          piece->piece_tracker->slow();
          break;
        case MotorPieceState::STOPPED:
          piece->piece_tracker->stop();
          break;
        default:
          break;
        }
      }
    }
    data->workpieces = !data->workpieceList.isEmpty();
  }

private: //================================================ private variables
         //================================================
         // classes, STL containers, and structs
         // pointers
         // primitive types
         // bool and char
private: //================================================ private functions
         //================================================
         // void privateFunction();
};

#endif
