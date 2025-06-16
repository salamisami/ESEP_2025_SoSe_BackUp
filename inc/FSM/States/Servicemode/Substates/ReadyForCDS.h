#ifndef READYFORCDS_H
#define READYFORCDS_H
#pragma once

#include "State.h"
#include "CalDistanceSlow.h"

class ReadyForCDS : public State {
public: //============================================ constructors & destructors ============================================
    ReadyForCDS(ContextData* data) ;
    virtual ~ReadyForCDS();
	

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
