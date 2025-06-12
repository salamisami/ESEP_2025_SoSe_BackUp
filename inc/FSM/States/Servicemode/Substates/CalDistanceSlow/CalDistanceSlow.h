#ifndef CALDISTANCESLOW_H
#define CALDISTANCESLOW_H
#pragma once

#include "OrthogonalState.h"
#include "IdleCDS.h"
#include "IdleGateCDS.h"

class CalDistanceSlow : public OrthogonalState{
public: //============================================ contructors & destructors ============================================
    CalDistanceSlow(ContextData* data) ;
    virtual ~CalDistanceSlow();
	

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
