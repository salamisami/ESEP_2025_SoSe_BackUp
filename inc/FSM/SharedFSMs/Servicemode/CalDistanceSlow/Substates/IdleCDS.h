#ifndef IDLECDS_H
#define IDLECDS_H
#pragma once

#include "State.h"
#include "StartCDS.h"

class IdleCDS : public State {
public: //============================================ constructors & destructors ============================================
    IdleCDS(ContextData* data) ;
    virtual ~IdleCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* laser_front_unblocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
