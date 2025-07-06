#ifndef SERVICEMODESENDRAMP_H
#define SERVICEMODESENDRAMP_H
#pragma once

#include "OrthState.h"
#include "IdleSMSR.h"
#include "SendToRamp.h"
#include "ReadyForCDF.h"


class ServiceModeSendRamp : public OrthState {
public: //============================================ constructors & destructors ============================================
    ServiceModeSendRamp(ContextData* data);
	ServiceModeSendRamp(ContextData* data, std::deque<State*> initial_substates);
    virtual ~ServiceModeSendRamp();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	//State* laser_ramp_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
