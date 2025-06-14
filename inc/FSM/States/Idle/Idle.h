#ifndef IDLE_H
#define IDLE_H
#pragma once

#include "HState.h"
#include "Traffic_Green_On_Slow.h"

class Idle : public HState {
    //============================================ constructors & destructors ============================================
public:
    Idle(ContextData* data, HState* initial_substate = nullptr);
    virtual ~Idle();

    //================================================ public functions ================================================
public:
    State* button_start_released() override;

    void entry() override;
    void exit() override;


    //================================================ private variables ================================================
private:
    //void privateFunction();

//================================================ private functions ================================================
private:

};

#endif