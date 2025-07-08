#ifndef MACROS_H
#define MACROS_H
#pragma once

#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>


#include <stdexcept>
#include <string>

#define THROW(msg) throw std::runtime_error( \
    "Exception is occured at line: " + std::to_string(__LINE__) + " in " + __FILE__ + ": " + std::string(msg) \
)

#ifdef MOCK
#define WAIT(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#else
#define WAIT(x) usleep(x * 1000)
#endif


#define FILE_EXISTS(fname) (std::ifstream(fname).good())

#define RECORDER_CSV "ESEP-Team-1-1_25/events.csv"
#define PROFIL_DATEI "ESEP-Team-1-1_25/profile_calibration.csv"
#define SAVE_LOCATION_TIMEPROFILE "ESEP-Team-1-1_25/time_profiles.csv"

#define DEBUG(msg) std::cout << msg << std::endl
#endif

#ifdef VERBOSE_STATES
#define PRINT_STATE //std::cout << __PRETTY_FUNCTION__ << std::endl
#else
#define PRINT_STATE
#endif

#define DISTANCE_BETWEEN_PIECES 70
#define WAY_TO_AREA 80
#define OVER_AREA 20

#define UPDATE_PIECE_INTERVAL 100
#define PIECE_TRANSITION_TOLERANCE_BEFORE_ADC 25
#define PIECE_TRANSITION_TOLERANCE 25
#define PIECE_TRANSITION_TOLERANCE_GATE 25
#define SORT_OUT_TIME 3500
#define ADC_TIMEOUT_TIME 1500
#define GATE_THROUGHTIME 2000
#define PUSH_DELAY //muss noch gemessen werden

#define DEADLINE_FACTOR 1
#define TIMESTAMP_FACTOR 0.9
#define GATE_END_FACTOR 0.9

#define FBM_1
// Configuration for FBM Module 1
#ifdef FBM_1
	#define FBM					1
	#define FBM_N_HAL       	"Hal_1"
	#define FBM_N_FSM       	"Fsm_1"
	#define FBM_N_COM       	"Com_1"
	#define FBM_N_COM_EXT		"Com_2"
	#define FBM_N_COM_RECEIVER	"Com_receiver_1"
	#define FBM_N_RECORDER  	"Rec_1"
	#define FBM_N_REMOTE    	"Rem_1"
	#define FBM_N_DISPATCHER 	"Dis_1"
	#define RECEIVE_TOPIC		"festo/anlage1/status/"
	#define COMMAND_TOPIC		"festo/anlage1/command"
	#define MQTT_CLIENT			"Festo_FBM1"
#endif

#ifdef FBM_2
	// Default to FBM Module 2
	#define FBM					2
	#define FBM_N_HAL       	"Hal_2"
	#define FBM_N_FSM       	"Fsm_2"
	#define FBM_N_COM       	"Com_2"
	#define FBM_N_COM_EXT		"Com_1"
	#define FBM_N_COM_RECEIVER 	"Com_receiver_2"
	#define FBM_N_RECORDER  	"Rec_2"
	#define FBM_N_REMOTE   		"Rem_2"
	#define FBM_N_DISPATCHER 	"Dis_2"
	#define RECEIVE_TOPIC		"festo/anlage2/status/"
	#define COMMAND_TOPIC		"festo/anlage2/command"
	#define MQTT_CLIENT			"Festo_FBM2"
#endif
