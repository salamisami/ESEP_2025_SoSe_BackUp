#ifndef RAMPSTATUS_H
#define RAMPSTATUS_H
#pragma once

#include "HState.h"
#include "RampNotFull.h"


class RampStatus : public HState {
public: //============================================ constructors & destructors ============================================
    RampStatus(ContextData* data) ;
    virtual ~RampStatus();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
