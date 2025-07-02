#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#pragma once

#include "OrthState.h"

class ErrorHandler : public OrthState {
public: //============================================ constructors & destructors ============================================
    ErrorHandler(ContextData* data) ;
    virtual ~ErrorHandler();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	//State* laser_ramp_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif