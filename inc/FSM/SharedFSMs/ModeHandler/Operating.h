#ifndef OPERATING_H
#define OPERATING_H
#pragma once

#include "OrthState.h"
#include "IdleIM.h"
#include "PseudoState.h"

#include "MotorControl.h"
#include "PieceControllerFBM1.h"
#include "SortingOrder.h"
#include "StartingAreaTracker.h"
#include "ErrorHandler.h"

class Operating : public OrthState {
//============================================ constructors & destructors ============================================
public:
	Operating(ContextData* data);
	Operating(ContextData* data, std::deque<State*> initial_substates);
    virtual ~Operating();
	
//================================================ public functions ================================================
public:
    void entry() override;
    void exit() override;

    State* clone() override;
    
    State* button_stop_pressed() override;
    

//================================================ private variables ================================================
private:
	
//================================================ private functions ================================================
private:
	//int myVariable
	
};

#endif
