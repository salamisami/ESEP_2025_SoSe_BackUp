#ifndef MACROS_H
#define MACROS_H
#pragma once

#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>


#define THROW(msg) throw std::runtime_error(std::string(__FUNCTION__) + ": " + msg)
#define WAIT(x) usleep(x * 1000000)


#endif
