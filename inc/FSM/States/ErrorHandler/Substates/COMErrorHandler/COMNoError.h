#ifndef COMNOERROR_H
#define COMNOERROR_H
#pragma once

#include "State.h"
#include "COMFehlerUnquittiert.h"

class COMNoError : public State {
public: //============================================ constructors & destructors ============================================
    COMNoError(ContextData* data) ;
    virtual ~COMNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* error_c_lost_com() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif