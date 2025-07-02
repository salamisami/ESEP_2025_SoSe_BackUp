#ifndef OPERATINGMOCK_H
#define OPERATINGMOCK_H
#pragma once

#include "OrthState.h"
#include "MotorDisable.h"
#include "TrafficMock.h"
#include "IdleMock.h"

class OperatingMock : public OrthState {
public: //============================================ constructors & destructors ============================================
	OperatingMock(ContextData* data);    
	OperatingMock(ContextData* data, std::vector<State*> cloned_substates);
    virtual ~OperatingMock();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;
	State* button_stop_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
