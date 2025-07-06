#ifndef TRAFFICMOCK_H
#define TRAFFICMOCK_H
#pragma once

#include "HState.h"
#include "Green.h"

class TrafficMock : public HState {
public: //============================================ constructors & destructors ============================================
    TrafficMock(ContextData* data);
	TrafficMock(ContextData* data, State* initial_substate);
    virtual ~TrafficMock();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;
    
	State* laser_front_blocked() override;


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
