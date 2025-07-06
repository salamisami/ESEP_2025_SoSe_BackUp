#ifndef IDLESMSR_H
#define IDLESMSR_H
#pragma once

#include "State.h"
#include "CalibrationDoneSMSR.h"

class IdleSMSR : public State {
public: //============================================ constructors & destructors ============================================
    IdleSMSR(ContextData* data) ;
    virtual ~IdleSMSR();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

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
