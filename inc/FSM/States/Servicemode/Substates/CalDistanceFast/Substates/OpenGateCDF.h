#ifndef OPENGATECDF_H
#define OPENGATECDF_H
#pragma once

#include "HState.h"
#include "IdleGateCDF.h"

class OpenGateCDF : public HState {
public: //============================================ constructors & destructors ============================================
    OpenGateCDF(ContextData* data) ;
    virtual ~OpenGateCDF();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* timer(TIMER_ID id) override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
