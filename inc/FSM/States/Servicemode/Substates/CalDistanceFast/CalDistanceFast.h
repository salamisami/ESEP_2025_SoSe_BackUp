#ifndef CALDISTANCEFAST_H
#define CALDISTANCEFAST_H
#pragma once

#include "OrthogonalState.h"
#include "IdleCDF.h"
#include "IdleGateCDF.h"

class CalDistanceFast : public OrthogonalState{
public: //============================================ contructors & destructors ============================================
    CalDistanceFast(ContextData* data) ;
    virtual ~CalDistanceFast();
	

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
