#ifndef STARTCDF_H
#define STARTCDF_H
#pragma once

#include "HState.h"
#include "StopCDF.h"

class StartCDF : public HState {
public: //============================================ constructors & destructors ============================================
    StartCDF(ContextData* data) ;
    virtual ~StartCDF();
	

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
