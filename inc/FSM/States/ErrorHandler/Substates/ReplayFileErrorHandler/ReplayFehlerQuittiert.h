#ifndef REPLAYFEHLERQUITTIERT_H
#define REPLAYFEHLERQUITTIERT_H
#pragma once

#include "State.h"

class ReplayFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    ReplayFehlerQuittiert(ContextData* data) ;
    virtual ~ReplayFehlerQuittiert();
	

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