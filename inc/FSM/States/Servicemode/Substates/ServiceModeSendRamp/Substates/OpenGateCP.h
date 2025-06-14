#ifndef OPENGATECP_H
#define OPENGATECP_H
#pragma once

#include "HState.h"
#include "IdleGateCP.h"

class OpenGateCP : public HState {
public: //============================================ constructors & destructors ============================================
    OpenGateCP(ContextData* data) ;
    virtual ~OpenGateCP();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

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
