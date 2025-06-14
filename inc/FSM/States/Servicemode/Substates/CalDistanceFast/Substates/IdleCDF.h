#ifndef IDLECDF_H
#define IDLECDF_H
#pragma once

#include "HState.h"
#include "StartCDF.h"

class IdleCDF : public HState {
public: //============================================ constructors & destructors ============================================
    IdleCDF(ContextData* data) ;
    virtual ~IdleCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

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
