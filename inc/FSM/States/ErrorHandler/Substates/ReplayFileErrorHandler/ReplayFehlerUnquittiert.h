#ifndef REPLAYFEHLERUNQUITTIERT_H
#define REPLAYFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "ReplayFehlerQuittiert.h"

class ReplayFehlerUnquittiert  : public State {
public: //============================================ constructors & destructors ============================================
    ReplayFehlerUnquittiert(ContextData* data) ;
    virtual ~ReplayFehlerUnquittiert();
	

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