#ifndef PIECELOSTFEHLERUNQUITTIERT_H
#define PIECELOSTFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "PieceLostFehlerQuittiert.h"

class PieceLostFehlerUnquittiert  : public State {
public: //============================================ constructors & destructors ============================================
    PieceLostFehlerUnquittiert(ContextData* data) ;
    virtual ~PieceLostFehlerUnquittiert();
	

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