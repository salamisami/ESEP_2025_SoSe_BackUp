#ifndef RUNMOTOR_H
#define RUNMOTOR_H
#pragma once

#include "State.h"
#include "SimulatePiece.h"

class RunMotor : public State {
public: //============================================ constructors & destructors ============================================
    RunMotor(ContextData* data) ;
    virtual ~RunMotor();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_front_unblocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers

	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
