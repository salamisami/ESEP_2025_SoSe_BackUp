#ifndef OPENGATECRS_H
#define OPENGATECRS_H
#pragma once

#include "State.h"
#include "PieceAtGateCRS.h"

class OpenGateCRS : public State {
public: //============================================ constructors & destructors ============================================
    OpenGateCRS(ContextData* data) ;
    virtual ~OpenGateCRS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
