#ifndef SLOWTEMP_H
#define SLOWTEMP_H
#pragma once

#include "State.h"
#include "Fast.h"

class SlowTemp : public State {
public: //============================================ constructors & destructors ============================================
    SlowTemp(ContextData* data) ;
    virtual ~SlowTemp();
	

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
