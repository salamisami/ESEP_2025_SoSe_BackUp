#ifndef MACROS_H
#define MACROS_H
#pragma once

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

#include <stdexcept>
#include <string>

#define THROW(msg)                                                             \
  throw std::runtime_error(                                                    \
      "Exception is occured at line: " + std::to_string(__LINE__) + " in " +   \
      __FILE__ + ": " + std::string(msg))

#ifdef MOCK
#define WAIT(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#else
#define WAIT(x) usleep(x * 1000)
#endif

#define FILE_EXISTS(fname) (std::ifstream(fname).good())

#define RECORDER_CSV "ESEP-Team-1-1_25/events.csv"
#define PROFIL_DATEI "ESEP-Team-1-1_25/profile_calibration.csv"
#define SAVE_LOCATION_TIMEPROFILE "ESEP-Team-1-1_25/time_profiles.csv"

#define BROKER_ADR "tcp://192.168.101.7:1883"

#ifdef NO_DEBUG
#define DEBUG(msg)
#else
#define DEBUG(msg) std::cout << msg << std::endl
#endif

#ifdef VERBOSE_STATES
#define PRINT_STATE std::cout << __PRETTY_FUNCTION__ << std::endl
#else
#define PRINT_STATE
#endif

#define DISTANCE_BETWEEN_PIECES 50
#define WAY_TO_AREA 80
#define OVER_AREA 20

#define UPDATE_PIECE_INTERVAL 100
#define PIECE_TRANSITION_TOLERANCE_BEFORE_ADC 25
#define PIECE_TRANSITION_TOLERANCE 25
#define PIECE_TRANSITION_TOLERANCE_GATE 25

#define MOTOR_SLOW_POS_AT_START_ADC 80

#define PIECE_TRANSFER_DURATION 2000
#define SORT_OUT_TIME 4000
#define ADC_TIMEOUT_TIME 2000
#define GATE_THROUGHTIME 2000
#define PUSH_DELAY // muss noch gemessen werden


//piece appeared: runterstellen
//piece missing: hochstellen
#define TIMESTAMP_FACTOR 1.05
#define GATE_END_FACTOR 1.05


#define DEADLINE_FACTOR 1

// Configuration for FBM Module 1
#ifdef FBM_1
#define FBM 1
#define FBM_N_HAL "Hal_1"
#define FBM_N_FSM "Fsm_1"
#define FBM_N_COM "Com_1"
#define FBM_N_COM_EXT "Com_2"
#define FBM_N_COM_RECEIVER "Com_receiver_1"
#define FBM_N_RECORDER "Rec_1"
#define FBM_N_REMOTE "Rem_1"
#define FBM_N_DISPATCHER "Dis_1"
#define RECEIVE_TOPIC "festo/anlage1/status/"
#define COMMAND_TOPIC "festo/anlage1/command"
#define MQTT_CLIENT "Festo_FBM1"
#endif

#ifdef FBM_2
// Default to FBM Module 2
#define FBM 2
#define FBM_N_HAL "Hal_2"
#define FBM_N_FSM "Fsm_2"
#define FBM_N_COM "Com_2"
#define FBM_N_COM_EXT "Com_1"
#define FBM_N_COM_RECEIVER "Com_receiver_2"
#define FBM_N_RECORDER "Rec_2"
#define FBM_N_REMOTE "Rem_2"
#define FBM_N_DISPATCHER "Dis_2"
#define RECEIVE_TOPIC "festo/anlage2/status/"
#define COMMAND_TOPIC "festo/anlage2/command"
#define MQTT_CLIENT "Festo_FBM2"
#endif


#define MACRO_PIECE_MISSING_PT1                                                \
  data->sender->send_event((int8_t)Topic::ERROR,                               \
                           (int)Error_Enum::ERROR_W_LOST);                     \
  data->sender->send_event((int8_t)Topic::DELETE_W_MOTOR,                      \
                           (int)localdata_.piece->id);                         \
  PieceEnum validated_piece = localdata_.validated_type;                       \
  switch (validated_piece) {                                                   \
  case PieceEnum::FLAT:                                                        \
    data->sender->send_event((int8_t)Topic::INTERNAL,                          \
                             (int)Internal_Enum::RESET_TO_FLAT);               \
    break;                                                                     \
  case PieceEnum::TALL:                                                        \
    data->sender->send_event((int8_t)Topic::INTERNAL,                          \
                             (int)Internal_Enum::RESET_TO_TALL);               \
    break;                                                                     \
  case PieceEnum::TALL_WITH_METAL:                                             \
    data->sender->send_event((int8_t)Topic::INTERNAL,                          \
                             (int)Internal_Enum::RESET_TO_TALL_W_METAL);       \
    break;                                                                     \
  default:                                                                     \
    break;                                                                     \
  }                                                                            \
  Piece *piece_to_delete = localdata_.piece;                                   \
  data->pieces_map->erase(localdata_.piece->id);                               \
  delete piece_to_delete;                                                      \
  return State::EXIT_STATE;

// In your MotorStateMacros.h or similar header
#define AREA_AS_INT_TO_STATE(data, state_int)                                  \
  ((state_int) == 0)   ? static_cast<State *>(new Fast(data))                  \
  : ((state_int) == 1) ? static_cast<State *>(new Slow(data))                  \
  : ((state_int) == 2) ? static_cast<State *>(new Stop(data))                  \
                       : nullptr

// MotorControl//MotorControl//MotorControl//MotorControl//MotorControl//MotorControl//MotorControl
#define TOPIC_TO_MOTOR_STATE(topic)                                            \
  ((topic) == static_cast<int8_t>(Topic::MOTOR_STOP_FSM)                       \
       ? MotorPieceState::STOPPED                                              \
       : ((topic) == static_cast<int8_t>(Topic::MOTOR_SLOW)                    \
              ? MotorPieceState::SLOW                                          \
              : ((topic) == static_cast<int8_t>(Topic::MOTOR_FAST)             \
                     ? MotorPieceState::FAST                                   \
                     : ((topic) == static_cast<int8_t>(Topic::DELETE_W_MOTOR)  \
                            ? MotorPieceState::DELETE_W_MOTOR                  \
                            : static_cast<MotorPieceState>(-1)))))


#endif