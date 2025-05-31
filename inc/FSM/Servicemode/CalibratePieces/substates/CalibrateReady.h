#ifndef CALIBRATEREADY_H
#define CALIBRATEREADY_H
#pragma once

#include "State.h"
#include "Calibrating.h"

class CalibrateReady : public State{
public: //============================================ contructors & destructors ============================================
    CalibrateReady(ContextData* data);
    virtual ~CalibrateReady();
	

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