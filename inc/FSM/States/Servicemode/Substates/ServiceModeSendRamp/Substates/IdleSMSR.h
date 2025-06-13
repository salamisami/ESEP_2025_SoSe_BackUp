#ifndef IDLESMSR_H
#define IDLESMSR_H
#pragma once

#include "State.h"
#include "CalibrationDoneSMSR.h"

class IdleSMSR : public State {
public: //============================================ contructors & destructors ============================================
    IdleSMSR(ContextData* data) ;
    virtual ~IdleSMSR();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	I_State* adc_calibration_done() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
