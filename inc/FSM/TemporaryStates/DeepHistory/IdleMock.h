#ifndef IDLEMOCK_H
#define IDLEMOCK_H
#pragma once

#include "State.h"
#include "OperatingMock.h"

class IdleMock : public State {
public: //============================================ constructors & destructors ============================================
    IdleMock(ContextData* data) ;
    virtual ~IdleMock();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* button_start_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
