#ifndef ADC_PT1_H
#define ADC_PT1_H
#pragma once

#include "State.h"
#include "Measuring_PT1.h"
#include "LocalDataPT1.h"

class ADC_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    ADC_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~ADC_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* adc_new_piece() override;
	State* adc_timeout() override;
    


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
