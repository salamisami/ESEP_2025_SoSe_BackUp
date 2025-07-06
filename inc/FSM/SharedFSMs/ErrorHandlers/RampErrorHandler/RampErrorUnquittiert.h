#ifndef RAMPERRORUNQUITTIERT_H
#define RAMPERRORUNQUITTIERT_H
#pragma once

#include "State.h"
#include "RampErrorQuittiert.h"
#include "RampErrorResolvedUnquittiert.h"

class RampErrorUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    RampErrorUnquittiert(ContextData* data) ;
    virtual ~RampErrorUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* ramp_not_full() override;
	State* com_ramp_not_full() override;
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