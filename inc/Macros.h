#ifndef MACROS_H
#define MACROS_H
#pragma once

#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>


#define THROW(msg) throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + ": " + msg)

#ifdef MOCK
#define WAIT(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#else
#define WAIT(x) usleep(x * 1000)
#endif

#define DEBUG(msg) std::cout << msg << std::endl
#endif
