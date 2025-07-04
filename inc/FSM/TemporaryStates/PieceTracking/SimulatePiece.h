#ifndef SIMULATEPIECE_H
#define SIMULATEPIECE_H
#pragma once

#include "OrthState.h"
#include "FastTemp.h"
#include "LetPieceThrough.h"
#include "IdleTest.h"
#include "TimeProfileManager.h"

class SimulatePiece : public OrthState {
public: //============================================ constructors & destructors ============================================
    SimulatePiece(ContextData* data) ;
    virtual ~SimulatePiece();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* laser_back_blocked() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
