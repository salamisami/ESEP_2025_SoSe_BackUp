#ifndef IDLEGATECDS_H
#define IDLEGATECDS_H
#pragma once

#include "State.h"
#include "OpenGateCDS.h"

class IdleGateCDS : public State {
public: //============================================ constructors & destructors ============================================
    IdleGateCDS(ContextData* data) ;
    virtual ~IdleGateCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	I_State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
