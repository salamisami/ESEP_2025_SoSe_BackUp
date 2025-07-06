#ifndef VALIDMEASURE_H
#define VALIDMEASURE_H
#pragma once

#include "State.h"
#include "MeasureFehlerUnquittiert.h"

class ValidMeasure : public State {
public: //============================================ constructors & destructors ============================================
    ValidMeasure(ContextData* data) ;
    virtual ~ValidMeasure();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* adc_invalid_measure() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif