#ifndef GATETOENDCDS_H
#define GATETOENDCDS_H
#pragma once

#include "State.h"
#include "CalRampSlow.h"

class GateToEndCDS : public State {
public: //============================================ constructors & destructors ============================================
    GateToEndCDS(ContextData* data) ;
    virtual ~GateToEndCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_back_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
