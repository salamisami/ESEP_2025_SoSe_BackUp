#ifndef SERVICEMODESENDRAMP_H
#define SERVICEMODESENDRAMP_H
#pragma once

#include "OrthState.h"
#include "IdleSMSR.h"
#include "SendToRamp.h"


class ServiceModeSendRamp : public OrthState {
public: //============================================ constructors & destructors ============================================
    ServiceModeSendRamp(ContextData* data) ;
    virtual ~ServiceModeSendRamp();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_ramp_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
