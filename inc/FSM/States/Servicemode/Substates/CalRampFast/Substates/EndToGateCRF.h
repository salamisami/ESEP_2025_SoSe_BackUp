#ifndef ENDTOGATECRF_H
#define ENDTOGATECRF_H
#pragma once

#include "State.h"
#include "OpenGateCRF.h"

class EndToGateCRF : public State {
public: //============================================ constructors & destructors ============================================
    EndToGateCRF(ContextData* data) ;
    virtual ~EndToGateCRF();
	

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
