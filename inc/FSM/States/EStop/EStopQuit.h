#ifndef ESTOPQUIT_H
#define ESTOPQUIT_H
#pragma once

#include "State.h"

class EStopQuit: public State{
public: //============================================ contructors & destructors ============================================
    EStopQuit(ContextData* data);
    virtual ~EStopQuit();
	

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif