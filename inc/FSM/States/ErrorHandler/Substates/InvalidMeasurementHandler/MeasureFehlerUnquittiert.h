#ifndef MEASUREFEHLERUNQUITTIERT_H
#define MEASUREFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "MeasureFehlerQuittiert.h"
#include "ADCFreiUnquittiert.h"

class MeasureFehlerUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    MeasureFehlerUnquittiert(ContextData* data) ;
    virtual ~MeasureFehlerUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* adc_top_area_unblocked() override;
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