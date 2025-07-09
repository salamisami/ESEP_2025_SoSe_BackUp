#ifndef STOPWATCH_H
#define STOPWATCH_H
#pragma once

#include "Macros.h"

#include <chrono>
#include <mutex>
#include <thread>


class Stopwatch {
public: //============================================ constructors & destructors ============================================
	Stopwatch() = default;
	virtual ~Stopwatch() = default;


public: //================================================ public functions ================================================
	/**
	 * @brief starts a stopwatch. If it's called more than once, the previous stopwatch will be discarded
	 */
	void start();
	/**
	 * @brief stops a stopwatch. If it's called without start(), it will throw an exception
	 * @return the duration of the stopwatch in miliseconds
	 */
	long stop();

	long peek_time();

	void reset();



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::mutex mtx;
	std::chrono::time_point<std::chrono::steady_clock> start_time;
	std::chrono::milliseconds accumulated_time{ 0 }; // Stores paused time
	//pointers
	//primitive types
	//bool and char
	bool is_running = false;
	bool is_reset = false;



private: //================================================ private functions ================================================

};

#endif