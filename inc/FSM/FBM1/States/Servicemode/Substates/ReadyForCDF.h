#ifndef READYFORCDF_H
#define READYFORCDF_H
#pragma once

#include "State.h"
#include "CalDistanceFast.h"

class ReadyForCDF : public State {
public: //============================================ constructors & destructors ============================================
    ReadyForCDF(ContextData* data) ;
    virtual ~ReadyForCDF();
	

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
