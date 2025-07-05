#ifndef CALIBWARNING_H
#define CALIBWARNING_H
#pragma once

#include "State.h"
#include "CalibNoWarning.h"

class CalibWarning : public State {
public: //============================================ constructors & destructors ============================================
    CalibWarning(ContextData* data) ;
    virtual ~CalibWarning();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif