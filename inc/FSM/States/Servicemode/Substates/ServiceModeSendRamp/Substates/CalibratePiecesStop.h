#ifndef CALIBRATEPIECESSTOP_H
#define CALIBRATEPIECESSTOP_H
#pragma once

#include "State.h"
#include "CalDistanceFast.h"

class CalibratePiecesStop : public State {
public: //============================================ contructors & destructors ============================================
    CalibratePiecesStop(ContextData* data) ;
    virtual ~CalibratePiecesStop();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    
	I_State* laser_front_blocked() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
