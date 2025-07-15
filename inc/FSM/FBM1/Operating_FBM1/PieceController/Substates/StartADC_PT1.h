#ifndef STARTADC_PT1_H
#define STARTADC_PT1_H
#pragma once

#include "State.h"
#include "ADC_PT1.h"
#include "LocalDataPT1.h"
#include "PendingTransferRequestNotAtEnd.h"

class StartADC_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    StartADC_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~StartADC_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	LocalDataPT1 localdata_;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
