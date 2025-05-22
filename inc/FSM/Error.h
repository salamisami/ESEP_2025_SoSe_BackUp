#ifndef ERROR_H
#define ERROR_H
#pragma once

#include "State.h"

class Error : public State {
public: //============================================ contructors & destructors ============================================
    Error(ContextData* data);
    virtual ~Error();
	

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