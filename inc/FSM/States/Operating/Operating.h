#ifndef OPERATING_H
#define OPERATING_H
#pragma once

#include "HState.h"
#include "IdleMode.h"
#include "SortingOrder.h"

class Operating : public HState {
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