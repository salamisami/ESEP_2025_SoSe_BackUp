#ifndef CALIBRATIONDONESMSR_H
#define CALIBRATIONDONESMSR_H
#pragma once

#include "State.h"
#include "ReadyForCDF.h"

class CalibrationDoneSMSR : public State {
public: //============================================ constructors & destructors ============================================
    CalibrationDoneSMSR(ContextData* data) ;
    virtual ~CalibrationDoneSMSR();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_ramp_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
