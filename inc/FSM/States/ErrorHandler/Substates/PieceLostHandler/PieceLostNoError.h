#ifndef PIECELOSTNOERROR_H
#define PIECELOSTNOERROR_H
#pragma once

#include "State.h"

class PieceLostNoError : public State {
public: //============================================ constructors & destructors ============================================
    PieceLostNoError(ContextData* data) ;
    virtual ~PieceLostNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* error_w_lost() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif