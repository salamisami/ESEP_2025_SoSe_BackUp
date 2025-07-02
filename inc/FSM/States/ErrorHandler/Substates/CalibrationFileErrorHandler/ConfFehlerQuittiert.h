#ifndef CONFFEHLERQUITTIERT_H
#define CONFFEHLERQUITTIERT_H
#pragma once

#include "State.h"
#include "CalibNoError.h"

class ConfFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    ConfFehlerQuittiert(ContextData* data) ;
    virtual ~ConfFehlerQuittiert();
	

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