#ifndef CALIBRATIONFINISHED_H
#define CALIBRATIONFINISHED_H
#pragma once

#include "State.h"

class CalibrationFinished : public State {
public: //============================================ constructors & destructors ============================================
    CalibrationFinished(ContextData* data) ;
    virtual ~CalibrationFinished();
	

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
