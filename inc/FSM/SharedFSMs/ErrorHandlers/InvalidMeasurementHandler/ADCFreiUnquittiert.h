#ifndef ADCFREIUNQUITTIERT_H
#define ADCFREIUNQUITTIERT_H
#pragma once

#include "State.h"
#include "ValidMeasure.h"

class ADCFreiUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    ADCFreiUnquittiert(ContextData* data) ;
    virtual ~ADCFreiUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

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