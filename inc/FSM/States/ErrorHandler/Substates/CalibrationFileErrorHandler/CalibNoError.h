#ifndef CALIBNOERROR_H
#define CALIBNOERROR_H
#pragma once

#include "State.h"
#include "ConfFehlerUnquittiert.h"

class CalibNoError : public State {
public: //============================================ constructors & destructors ============================================
    CalibNoError(ContextData* data) ;
    virtual ~CalibNoError();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* cant_find_calb_conf() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif