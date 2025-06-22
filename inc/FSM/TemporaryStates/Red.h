#ifndef RED_H
#define RED_H
#pragma once

#include "State.h"
#include "Green.h"

class Red : public State {
public: //============================================ constructors & destructors ============================================
    Red(ContextData* data) ;
    virtual ~Red();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* button_start_pressed() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
