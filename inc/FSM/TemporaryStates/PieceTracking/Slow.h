#ifndef SLOW_H
#define SLOW_H
#pragma once

#include "State.h"
#include "Fast.h"

class Slow : public State {
public: //============================================ constructors & destructors ============================================
    Slow(ContextData* data) ;
    virtual ~Slow();
	

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
