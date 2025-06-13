#ifndef SERVICEMODESENDRAMP_H
#define SERVICEMODESENDRAMP_H
#pragma once

#include "OrthogonalState.h"
#include "IdleSMSR.h"
#include "IdleGateCP.h"


class ServiceModeSendRamp : public OrthogonalState {
public: //============================================ contructors & destructors ============================================
    ServiceModeSendRamp(ContextData* data) ;
    virtual ~ServiceModeSendRamp();
	

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
