#ifndef MEASUREFEHLERQUITTIERT_H
#define MEASUREFEHLERQUITTIERT_H
#pragma once

#include "State.h"
#include "ADCFrei.h"

class MeasureFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    MeasureFehlerQuittiert(ContextData* data) ;
    virtual ~MeasureFehlerQuittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* adc_top_area_unblocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif