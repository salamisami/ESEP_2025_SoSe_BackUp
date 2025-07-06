#ifndef SYSTEMSRAMPSTATUS_H
#define SYSTEMSRAMPSTATUS_H
#pragma once

#include "HState.h"
#include "NoRampFull.h"

class SystemsRampStatus : public HState {
public: //============================================ constructors & destructors ============================================
    SystemsRampStatus(ContextData* data) ;
    virtual ~SystemsRampStatus();
	

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
