#ifndef STARTCDF_H
#define STARTCDF_H
#pragma once

#include "State.h"
#include "PieceAtADCCDF.h"

class StartCDF : public State {
public: //============================================ constructors & destructors ============================================
    StartCDF(ContextData* data) ;
    virtual ~StartCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* adc_top_area_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
