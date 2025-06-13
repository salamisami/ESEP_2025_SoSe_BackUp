#ifndef OPENGATECP_H
#define OPENGATECP_H
#pragma once

#include "State.h"
#include "IdleGateCP.h"

class OpenGateCP : public State {
public: //============================================ contructors & destructors ============================================
    OpenGateCP(ContextData* data) ;
    virtual ~OpenGateCP();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	I_State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
