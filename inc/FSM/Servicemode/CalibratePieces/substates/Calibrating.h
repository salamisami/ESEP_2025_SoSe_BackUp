#ifndef CALIBRATING_H
#define CALIBRATING_H
#pragma once

#include "State.h"
#include "CalibrationDone.h"

class Calibrating : public State {
public: //============================================ contructors & destructors ============================================
    Calibrating(ContextData* data);
    virtual ~Calibrating();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* adc_calibration_done() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif