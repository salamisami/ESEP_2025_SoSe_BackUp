#ifndef PIECE_H
#define PIECE_H
#pragma once

#include "Macros.h"

#include <cstdint>
#include <thread>

#define TIMESTAMP_LENGTH 6

enum class Area : uint8_t {
	START_ADC = 0,
	ADC,
	ADC_GATE,
	GATE,
	GATE_END,
	GATE_RAMP
};

enum class Timestamp : uint8_t {
	ADC_BLOCKED = 0,
	ADC_UNBLOCKED,
	LASER_GATE_BLOCKED,
	LASER_GATE_UNBLOCKED,
	END,
	LASER_RAMP_BLOCKED
};


// 	START_ADC = 0
// 	ADC 1,
// 	ADC_GATE 2,
// 	GATE 3,
// 	GATE_END 4,
// 	GATE_RAMP 5,

typedef struct {
	double slow_speed[6];
	double fast_speed[6];
} Speed;


typedef struct {
	long slow[6];
	long fast[6];
} Deadlines;

/**
 * 0: ADC_BLOCKED
 * 1: ADC_UNBLOCKED
 * 2: LASER_GATE_BLOCKED
 * 3: LASER_GATE_UNBLOCKED
 * 4: END
 * 5: LASER_RAMP_BLOCKED
 */
typedef struct {
	long timestamp[TIMESTAMP_LENGTH];
} TimeProfile;

class Piece {
public: //============================================ constructors & destructors ============================================
	/**
	 * @brief Creates a piece, by inserting time profile.
	 * @param input_profile the calibration profile of time stamps, which we got from the calibration in Servicemode
	 */
	Piece(TimeProfile input_profile_slow, TimeProfile input_profile_fast, uint8_t tick_duration = 100);
	virtual ~Piece();


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
	Deadlines deadlines;
	std::condition_variable cv_occupied;
	std::thread piece_thread;
	//Timer timer;
	//pointers
	//primitive types
	Speed speed;
	//bool and char
	bool running = false;
	volatile Area current_area = Area::START_ADC;
	volatile double current_position = 0;
	uint8_t mode = 0;
	uint8_t tick_duration;




private: //================================================ private functions ================================================
	//void privateFunction();
	Deadlines convert_to_deadlines(TimeProfile input_timetable_slow, TimeProfile input_timetable_fast);
	Speed convert_deadlines_to_speed(const Deadlines deadline);
	void thread_function();
	Area step(Area initial_area);

};

#endif
