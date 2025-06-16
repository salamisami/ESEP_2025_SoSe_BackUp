#ifndef OPERATING_H
#define OPERATING_H
#pragma once

#include "HState.h"
#include "Idle.h"

class Operating : public State {
//============================================ constructors & destructors ============================================
public:
    Operating(ContextData* data);
    virtual ~Operating();
	
//================================================ public functions ================================================
public:
    void entry() override;
    void exit() override;
    
    State* button_stop_pressed() override;
    

//================================================ private variables ================================================
private:
	
//================================================ private functions ================================================
private:
	//int myVariable
	
};

#endif