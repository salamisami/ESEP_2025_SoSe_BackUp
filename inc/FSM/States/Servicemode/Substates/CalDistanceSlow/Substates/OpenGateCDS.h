#ifndef OPENGATECDS_H
#define OPENGATECDS_H
#pragma once

#include "State.h"
#include "IdleGateCDS.h"

class OpenGateCDS : public State {
public: //============================================ contructors & destructors ============================================
    OpenGateCDS(ContextData* data) ;
    virtual ~OpenGateCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	I_State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
