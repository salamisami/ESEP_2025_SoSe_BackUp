#ifndef CALIBRATIONDONESMSR_H
#define CALIBRATIONDONESMSR_H
#pragma once

#include "HState.h"
#include "ReadyForCDF.h"

class CalibrationDoneSMSR : public HState {
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
