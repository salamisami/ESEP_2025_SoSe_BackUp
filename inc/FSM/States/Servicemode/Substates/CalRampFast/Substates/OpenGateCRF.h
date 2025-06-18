#ifndef OPENGATECRF_H
#define OPENGATECRF_H
#pragma once

#include "State.h"
#include "PieceAtGateCRF.h"

class OpenGateCRF : public State {
public: //============================================ constructors & destructors ============================================
    OpenGateCRF(ContextData* data) ;
    virtual ~OpenGateCRF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* timer(TIMER_ID id) override;
	State* laser_sorting_gate_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
