#ifndef NODEREDNOERROR_H
#define NODEREDNOERROR_H
#pragma once

#include "State.h"

class NodeRedNoError : public State {
public: //============================================ constructors & destructors ============================================
    NodeRedNoError(ContextData* data) ;
    virtual ~NodeRedNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* error_c_lost_nr() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif