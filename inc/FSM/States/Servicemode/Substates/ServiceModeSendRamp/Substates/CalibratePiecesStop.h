#ifndef CALIBRATEPIECESSTOP_H
#define CALIBRATEPIECESSTOP_H
#pragma once

#include "HState.h"
#include "CalDistanceFast.h"

class CalibratePiecesStop : public HState {
public: //============================================ constructors & destructors ============================================
    CalibratePiecesStop(ContextData* data) ;
    virtual ~CalibratePiecesStop();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	State* laser_front_blocked() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
