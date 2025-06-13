#ifndef STOPCDF_H
#define STOPCDF_H
#pragma once

#include "State.h"

class StopCDF : public State {
public: //============================================ contructors & destructors ============================================
    StopCDF(ContextData* data) ;
    virtual ~StopCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
