#ifndef FAST_H
#define FAST_H
#pragma once

#include "State.h"
#include "Slow.h"

class Fast : public State {
public: //============================================ constructors & destructors ============================================
    Fast(ContextData* data) ;
    virtual ~Fast();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_reset_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
