#ifndef ADCGATE_PT1_H
#define ADCGATE_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "PieceMissing_PT1.h"
#include "Gate_PT1.h"
#include "IsMetal_PT1.h"

class ADCGate_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    ADCGate_PT1(ContextData* data, LocalDataPT1 localdata);
    virtual ~ADCGate_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* timer(TIMER_ID id) override;
	State* laser_sorting_gate_blocked() override;
	State* metal_detected() override;
    


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
