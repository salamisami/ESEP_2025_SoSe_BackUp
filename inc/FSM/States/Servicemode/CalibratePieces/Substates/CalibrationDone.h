#ifndef CALIBRATIONDONE_H
#define CALIBRATIONDONE_H
#pragma once

#include "State.h"

class CalibrationDone: public State {
public: //============================================ contructors & destructors ============================================
    CalibrationDone(ContextData* data);
    virtual ~CalibrationDone();
	

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