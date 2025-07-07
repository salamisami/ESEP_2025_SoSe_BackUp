#ifndef SENDTORAMP_H
#define SENDTORAMP_H
#pragma once

#include "HState.h"
#include "IdleSTR.h"

class SendToRamp : public HState {
public: //============================================ constructors & destructors ============================================
    SendToRamp(ContextData* data) ;
	SendToRamp(ContextData* data, State* initial_substate);
    virtual ~SendToRamp();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* clone() override;

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
