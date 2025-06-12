#ifndef IDLESERVICEMODE_H
#define IDLESERVICEMODE_H
#pragma once

#include "State.h"
#include "CalDistanceSlow.h"

class IdleServiceMode : public State {
public: //============================================ contructors & destructors ============================================
    IdleServiceMode(ContextData* data) ;
    virtual ~IdleServiceMode();
	

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
