#ifndef ENDTOGATECRS_H
#define ENDTOGATECRS_H
#pragma once

#include "State.h"
#include "OpenGateCRS.h"

class EndToGateCRS : public State {
public: //============================================ constructors & destructors ============================================
    EndToGateCRS(ContextData* data) ;
    virtual ~EndToGateCRS();
	

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
