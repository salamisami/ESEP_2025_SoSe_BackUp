#ifndef OPERATING_H
#define OPERATING_H
#pragma once

#include "State.h"
#include "Idle.h"
#include "StateA.h"
#include "EmergencyStop.h"
#include "Servicemode.h"

class Operating : public State {
//============================================ contructors & destructors ============================================
public:
    Operating(ContextData* data, State* previousState = nullptr);
    virtual ~Operating();
	
//================================================ public functions ================================================
public:
    void entry() override;
    void exit() override;
    
    State* stop() override;
    State* estop() override;
    State* forward() override;
    State* backward() override;

    State* tick() override;
    State* service() override;
    State* reset() override;
    

//================================================ private variables ================================================
private:
    State* subState;
	
//================================================ private functions ================================================
private:
	//int myVariable
	
};

#endif