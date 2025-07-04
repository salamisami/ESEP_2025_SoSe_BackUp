#ifndef CALIBNOWARNING_H
#define CALIBNOWARNING_H
#pragma once

#include "State.h"
#include "CalibWarning.h"

class CalibNoWarning : public State {
public: //============================================ constructors & destructors ============================================
    CalibNoWarning(ContextData* data) ;
    virtual ~CalibNoWarning();
	

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