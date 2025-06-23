#ifndef OPENGATELPT_H
#define OPENGATELPT_H
#pragma once

#include "State.h"
#include "IdleLPT.h"

class OpenGateLPT : public State {
public: //============================================ constructors & destructors ============================================
    OpenGateLPT(ContextData* data, int duration);
    virtual ~OpenGateLPT();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	int duration;
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
