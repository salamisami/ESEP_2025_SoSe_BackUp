#ifndef CONFFEHLERUNQUITTIERT_H
#define CONFFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"
#include "ConfFehlerQuittiert.h"

class ConfFehlerUnquittiert : public State {
public: //============================================ constructors & destructors ============================================
    ConfFehlerUnquittiert(ContextData* data) ;
    virtual ~ConfFehlerUnquittiert();
	

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