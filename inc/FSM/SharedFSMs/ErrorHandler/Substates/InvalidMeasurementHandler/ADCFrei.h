#ifndef ADCFREI_H
#define ADCFREI_H
#pragma once

#include "State.h"
#include "ValidMeasure.h"

class ADCFrei : public State {
public: //============================================ constructors & destructors ============================================
    ADCFrei(ContextData* data) ;
    virtual ~ADCFrei();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif