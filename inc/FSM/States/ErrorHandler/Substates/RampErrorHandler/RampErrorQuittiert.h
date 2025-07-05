#ifndef RAMPERRORQUITTIERT_H
#define RAMPERRORQUITTIERT_H
#pragma once

#include "State.h"
#include "RampErrorResolved.h"

class RampErrorQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    RampErrorQuittiert(ContextData* data) ;
    virtual ~RampErrorQuittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* ramp_not_full() override;
	State* com_ramp_not_full() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif