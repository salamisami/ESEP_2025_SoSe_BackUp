#ifndef PIECETRACKER_H
#define PIECETRACKER_H
#pragma once


#include "Macros.h"
#include "Stopwatch.h"
#include "TimeProfileManager.h"
#include <cstdint>
#include <thread>
//#include <sys/neutrino.h>
//#include <sys/syspage.h>
#include <sched.h>
#include <utility>

#define TIMESTAMP_LENGTH 6

enum class Area : uint8_t {
	START_ADC = 0,
	ADC,
	ADC_GATE,

	GATE,
	GATE_END,
	GATE_RAMP
};


//  AREA:
// 	START_ADC = 0
// 	ADC 1,
// 	ADC_GATE 2,
// 	GATE 3,
// 	GATE_END 4,
// 	GATE_RAMP 5,

/**
 * 0: ADC_BLOCKED
 * 1: ADC_UNBLOCKED
 * 2: LASER_GATE_BLOCKED
 * 3: LASER_GATE_UNBLOCKED
 * 4: END
 * 5: LASER_RAMP_BLOCKED
 */


class PieceTracker {
public: //============================================ constructors & destructors ============================================
	PieceTracker(bool debug = true);
	virtual ~PieceTracker();


public: //================================================ public functions ================================================
	/**
	 * @brief tells the piece that the belt is running fast. This function should modify the rate of change of it's internal area and position.
	 */
	void fast();
	/**
	 * @brief tells the piece that the belt is running slow. This function should modify the rate of change of it's internal area and position.
	 */
	void slow();
	/**
	 * @brief tells the piece that the belt is stopped. Its internal are and position should be paused.
	 */
	void stop();

	void reset();



	void debug_mode(bool debug);

	/**
	 * @brief attempts to send the piece to the ramp
	 * @retval true if the send is valid
	 * @retval false if the send is not valid
	 */
	bool send_to_ramp();
	/**
	 * @brief returns current area of this piece
	 * @return the area, in which the piece is currently located
	 */
	Area getArea();
	/**
	 * @brief returns current position of current area. If the value is 50, means the piece is located exactly at the center of current area.
	 * @return the current position inside current area. The range of value is from 0 till 100
	 */
	double getPosition();



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread piece_thread;
	std::thread debug_thread;
	//Timer timer;
	//pointers
	//primitive types
	Stopwatch stopwatch;
	TimeProfile time_profile;
	//bool and char
	volatile bool running = false;
	Area current_area = Area::START_ADC;
	double current_position = 0;
	uint8_t current_mode = 0;
	bool debug = false;
	bool log = false;




private: //================================================ private functions ================================================
	std::pair<Area, double> timestamp_to_area_pos(const long& timestamp, const uint8_t& mode);
	long area_pos_to_timestamp(const Area& input_area, const double& position, const uint8_t mode);
	void debug_function();
	//void set_thread_priority(pthread_t thread, int priority);
	std::pair<Area, double> calculate_area_pos(const Area& input_area, const double& position, const uint8_t& mode);
	void update();
};

#endif
