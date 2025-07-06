#ifndef PUSHRAMPSTR_H
#define PUSHRAMPSTR_H
#pragma once

#include "State.h"
#include "IdleSTR.h"

class PushRampSTR : public State {
public: //============================================ constructors & destructors ============================================
    PushRampSTR(ContextData* data) ;
    virtual ~PushRampSTR();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
