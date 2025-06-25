#ifndef TIMEPROFILEMANAGER_H
#define TIMEPROFILEMANAGER_H
#pragma once

#include "PieceTracker.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // For std::runtime_error
#include <sstream>

#define SAVE_LOCATION_TIMEPROFILE "time_profiles.csv"


class TimeProfileManager {
public:
	// Saves time profiles to a file (overwrites if file exists)
	static void save_profile(const TimeProfile& timeprofile_fast, const TimeProfile& timeprofile_slow, const std::string& save_location) {
		std::ofstream file;
		file.open(save_location, std::ios::out);
		if(!file.is_open()) {
			THROW("Recorder: Datei konnte nicht geöffnet werden!");
		}
		file << "Fast, Slow\n";  // CSV-Header
		for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
			file << timeprofile_fast.timestamp[i] << "," << timeprofile_slow.timestamp[i] << "\n";
		}
		file.flush();
		file.close();
	}

	// Loads time profiles from a file (throws if file doesn't exist)
	static void load_profile(TimeProfile* timeprofile_fast_out, TimeProfile* timeprofile_slow_out, const std::string& load_location) {
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

		for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
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
				timeprofile_fast_out->timestamp[i] = std::stol(fast_str);
				timeprofile_slow_out->timestamp[i] = std::stol(slow_str);
			} catch(const std::invalid_argument& e) {
				std::cerr << "Error: Invalid number format at line " << i + 2 << "\n";
				break;
			}
		}
		in_file.close();
	}
private:

};

#endif
