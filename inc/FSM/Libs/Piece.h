#ifndef PIECE_H
#define PIECE_H
#pragma once

#include <cstdint>
#include <chrono>

enum class Area : uint8_t {
	START = 0,
	START_ADC,
	ADC,
	ADC_GATE,
	GATE,
	GATE_END,
	END,
	GATE_RAMP,
	RAMP
};

enum class Timestamp: uint8_t {
	ADC_BLOCKED = 0,
	ADC_UNBLOCKED,
	LASER_GATE_BLOCKED,
	LASER_GATE_UNBLOCKED,
	END,
	LASER_RAMP_BLOCKED
};

/**
 * 0: ADC_BLOCKED
 * 1: ADC_UNBLOCKED
 * 2: LASER_GATE_BLOCKED
 * 3: LASER_GATE_UNBLOCKED
 * 4: END
 * 5: LASER_RAMP_BLOCKED
 */
typedef struct {
	long timestamp[6];
} TimeProfile;

class Piece {
public: //============================================ constructors & destructors ============================================
	/**
	 * @brief Creates a piece, by inserting time profile.
	 * @param input_profile the calibration profile of time stamps, which we got from the calibration in Servicemode
	 */
	Piece(TimeProfile input_profile);
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
	TimeProfile profile;
	//pointers
	//primitive types
	//bool and char
	Area area;
	double position = 0;




private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif
