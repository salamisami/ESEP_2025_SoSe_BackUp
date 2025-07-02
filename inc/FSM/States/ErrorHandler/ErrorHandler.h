#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#pragma once

#include "OrthState.h"

class ErrorHandler : public OrthState {
public: //============================================ constructors & destructors ============================================
    ErrorHandler(ContextData* data);
	ErrorHandler(ContextData* data, std::vector<State*> initial_substates);
    virtual ~ErrorHandler();
	

public: //================================================ public functions ================================================
	State* clone() override;
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