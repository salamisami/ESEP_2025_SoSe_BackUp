#ifndef MACROS_H
#define MACROS_H
#pragma once

#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>


#define THROW(msg) throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + ": " + msg)
#define WAIT(x) usleep(x * 1000000)
#define DEBUG(msg) std::cout << msg << std::endl
#define PULSE_STOP_THREAD 1


#endif
