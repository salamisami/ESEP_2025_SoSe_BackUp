#ifndef GATETOENDCDF_H
#define GATETOENDCDF_H
#pragma once

#include "State.h"
#include "CalRampFast.h"

class GateToEndCDF : public State {
public: //============================================ constructors & destructors ============================================
    GateToEndCDF(ContextData* data) ;
    virtual ~GateToEndCDF();
	

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
