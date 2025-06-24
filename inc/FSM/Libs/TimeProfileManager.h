#ifndef TIMEPROFILEMANAGER_H
#define TIMEPROFILEMANAGER_H
#pragma once

#include "Piece.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // For std::runtime_error

#define SAVE_LOCATION "time_profiles.txt"


class TimeProfileManager {
public:
	// Saves time profiles to a text file (overwrites if exists)
	static void save_profile(
		const TimeProfile& timeprofile_fast,
		const TimeProfile& timeprofile_slow,
		const std::string& save_location
	) {
		std::ofstream out_file(save_location);
		if(!out_file) {
			throw std::runtime_error("Failed to open file for writing: " + save_location);
		}

		// Write fast profile timestamps (comma-separated)
		for(int i = 0; i < 6; ++i) {
			out_file << timeprofile_fast.timestamp[i];
			if(i < 5) out_file << ",";
		}
		out_file << "\n";

		// Write slow profile timestamps (comma-separated)
		for(int i = 0; i < 6; ++i) {
			out_file << timeprofile_slow.timestamp[i];
			if(i < 5) out_file << ",";
		}
		out_file << "\n";

		out_file.close();
	}

	// Loads time profiles from a text file (throws if file doesn't exist)
	static void load_profile(
		TimeProfile* timeprofile_fast_out,
		TimeProfile* timeprofile_slow_out,
		const std::string& load_location
	) {
		if(!check_time_profile(load_location)) {
			throw std::runtime_error("File does not exist: " + load_location);
		}

		std::ifstream in_file(load_location);
		if(!in_file) {
			throw std::runtime_error("Failed to open file for reading: " + load_location);
		}

		std::string line;

		// Read fast profile
		if(std::getline(in_file, line)) {
			std::stringstream ss(line);
			std::string token;
			for(int i = 0; i < 6 && std::getline(ss, token, ','); ++i) {
				timeprofile_fast_out->timestamp[i] = std::stol(token);
			}
		} else {
			throw std::runtime_error("Invalid file format (missing fast profile)");
		}

		// Read slow profile
		if(std::getline(in_file, line)) {
			std::stringstream ss(line);
			std::string token;
			for(int i = 0; i < 6 && std::getline(ss, token, ','); ++i) {
				timeprofile_slow_out->timestamp[i] = std::stol(token);
			}
		} else {
			throw std::runtime_error("Invalid file format (missing slow profile)");
		}

		in_file.close();
	}

	// Checks if a time profile file exists
	static bool check_time_profile(const std::string& location) {
		std::ifstream file(location);
		return file.good();
	}
};

#endif
