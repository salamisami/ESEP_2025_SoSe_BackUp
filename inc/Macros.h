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
#define PRINT_STATE std::cout << __PRETTY_FUNCTION__ << std::endl
#else
#define PRINT_STATE
#endif
