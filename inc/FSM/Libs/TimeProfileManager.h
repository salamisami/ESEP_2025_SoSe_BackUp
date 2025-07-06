#ifndef TIMEPROFILEMANAGER_H
#define TIMEPROFILEMANAGER_H
#pragma once

#include "TimeProfile.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // For std::runtime_error
#include <sstream>



class TimeProfileManager {
public:
	static void save_profile(const TimeProfile& timeprofile, const std::string& save_location) {
		std::ofstream file;
		file.open(save_location, std::ios::out);
		if(!file.is_open()) {
			throw std::runtime_error("TimeProfileManager: Datei konnte nicht geöffnet werden!");
		}
		file << "Fast, Slow\n";  // CSV-Header
		for(int i = 0; i < 6; i++) {
			file << timeprofile.fast_timestamps[i] << "," << timeprofile.slow_timestamps[i] << "\n";
		}
		file.flush();
		file.close();
	}

	static void load_profile(TimeProfile* time_profile, const std::string& load_location) {
		std::ifstream in_file(load_location);
		if(!in_file.is_open()) {
			std::cerr << "TimeProfile: Datei konnte nicht geöffnet werden!\n";
			return;
		}

		// Skip header (same as your save format)
		std::string line;
		if(!std::getline(in_file, line)) {
			std::cerr << "Error: Empty file\n";
			return;
		}

		for(int i = 0; i < 6; i++) {
			if(!std::getline(in_file, line)) {
				std::cerr << "Error: File has fewer lines than TIMESTAMP_LENGTH\n";
				break;
			}

			std::istringstream iss(line);
			std::string fast_str, slow_str;

			// Read exactly two comma-separated values per line
			if(!std::getline(iss, fast_str, ',') || !std::getline(iss, slow_str)) {
				std::cerr << "Error: Invalid line format at line " << i + 2 << "\n";
				break;
			}

			try {
				time_profile->fast_timestamps[i] = std::stol(fast_str) * TIMESTAMP_FACTOR;
				time_profile->slow_timestamps[i] = std::stol(slow_str); //TODO here also additional timestamp factor?
			} catch(const std::invalid_argument& e) {
				std::cerr << "Error: Invalid number format at line " << i + 2 << "\n";
				break;
			}
		}
		in_file.close();
		convert_to_deadlines(time_profile);
	}

public:
	static void convert_to_deadlines(TimeProfile* input_timetable) {
		input_timetable->slow_deadlines[0] = input_timetable->slow_timestamps[(int) Timestamp::ADC_BLOCKED];
		input_timetable->slow_deadlines[1] = input_timetable->slow_timestamps[(int) Timestamp::ADC_UNBLOCKED] - input_timetable->slow_timestamps[(int) Timestamp::ADC_BLOCKED];
		input_timetable->slow_deadlines[2] = input_timetable->slow_timestamps[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable->slow_timestamps[(int) Timestamp::ADC_UNBLOCKED];
		input_timetable->slow_deadlines[3] = input_timetable->slow_timestamps[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable->slow_timestamps[(int) Timestamp::LASER_GATE_BLOCKED];
		input_timetable->slow_deadlines[4] = input_timetable->slow_timestamps[(int) Timestamp::END] - input_timetable->slow_timestamps[(int) Timestamp::LASER_GATE_UNBLOCKED];
		input_timetable->slow_deadlines[5] = input_timetable->slow_timestamps[(int) Timestamp::LASER_RAMP_BLOCKED] - input_timetable->slow_timestamps[(int) Timestamp::LASER_GATE_BLOCKED];

		input_timetable->fast_deadlines[0] = input_timetable->fast_timestamps[(int) Timestamp::ADC_BLOCKED];
		input_timetable->fast_deadlines[1] = input_timetable->fast_timestamps[(int) Timestamp::ADC_UNBLOCKED] - input_timetable->fast_timestamps[(int) Timestamp::ADC_BLOCKED];
		input_timetable->fast_deadlines[2] = input_timetable->fast_timestamps[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable->fast_timestamps[(int) Timestamp::ADC_UNBLOCKED];
		input_timetable->fast_deadlines[3] = input_timetable->fast_timestamps[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable->fast_timestamps[(int) Timestamp::LASER_GATE_BLOCKED];
		input_timetable->fast_deadlines[4] = input_timetable->fast_timestamps[(int) Timestamp::END] - input_timetable->fast_timestamps[(int) Timestamp::LASER_GATE_UNBLOCKED];
		input_timetable->fast_deadlines[5] = input_timetable->fast_timestamps[(int) Timestamp::LASER_RAMP_BLOCKED] - input_timetable->fast_timestamps[(int) Timestamp::LASER_GATE_BLOCKED];
	}
};

#endif
