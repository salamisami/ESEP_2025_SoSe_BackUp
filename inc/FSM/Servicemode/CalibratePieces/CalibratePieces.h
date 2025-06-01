#ifndef CALIBRATEPIECES_H
#define CALIBRATEPIECES_H
#pragma once

#include "State.h"
#include "CalibrateReady.h"

class CalibratePieces : public State {
public: //============================================ contructors & destructors ============================================
	CalibratePieces(ContextData* data, State* initial_substate = nullptr);
	virtual ~CalibratePieces();


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