#ifndef MEASURING_PT1_H
#define MEASURING_PT1_H
#pragma once

#include "State.h"
#include "LocalDataPT1.h"
#include "ADCGate_PT1.h"

class Measuring_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    Measuring_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~Measuring_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* adc_wh_detect() override;
	State* adc_wf_detect() override;
	State* adc_wb_detect() override;
	
    State* adc_w_not_detect() override;
	State* adc_invalid_measure() override;

	State* laser_sorting_gate_blocked() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	LocalDataPT1 localdata_;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();

	State* goto_adcgate();
	
};

#endif
