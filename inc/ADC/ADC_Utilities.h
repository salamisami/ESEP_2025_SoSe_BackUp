#ifndef ADC_UTILITIES_H
#define ADC_UTILITIES_H
#pragma once

#include "TSCADC.h"
#include "ADC.h"
#include "Throw.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unistd.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <time.h>
#include <sstream>

#define REF_VOLTAGE 1.8f
#define SAMPLE_DELAY_NS 5000000L
#define TRIGGER_SCHRITT 0.1f
#define SAMPLE_COUNT 100
#define R25 1000.0f
#define R26 4700.0f
#define VOLTAGE_DIVIDER_FACTOR ((R25 + R26) / R25)
#define PROFIL_DATEI "ESEP-Team-1-1_25/profile_calibration.csv"
#define MESS_TOLERANZ  0.1f
#define MAX_WERT 400

typedef struct {
	std::string name;
	bool hatLoch;
	float avg;
	float lochMin;
	int lochStartIndex;
	int lochEndIndex;
} Profil;

class ADC_Utilities {
public: //============================================ contructors & destructors ============================================
	ADC_Utilities() = delete;
	ADC_Utilities(const ADC_Utilities&) = delete;
	ADC_Utilities& operator = (const ADC_Utilities&) = delete;

	virtual ~ADC_Utilities() = delete;


public: //================================================ public functions ================================================
	static void saveProfile(const Profil& p);
	static std::vector<Profil> loadProfile();
	static void calibrateComponents(ADC& adc, TSCADC& tscadc, float bandVoltage);
	static std::string classify(const std::vector<float>& value, const std::vector<Profil>& profile);
	static std::string executeMeasurement(ADC& adc, TSCADC& tscadc, float bandVoltage);
	static float define_band_voltage(ADC& adc, TSCADC& tscadc);
	



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char



private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif