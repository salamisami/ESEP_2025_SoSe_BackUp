#ifndef IDLE_H
#define IDLE_H
#pragma once

#include "State.h"
#include "Traffic_Green_On_Slow.h"

class Idle : public State {
    //============================================ contructors & destructors ============================================
public:
    Idle(ContextData* data, State* initial_substate = nullptr);
    virtual ~Idle();

    //================================================ public functions ================================================
public:
    I_State* button_start_released() override;

    void entry() override;
    void exit() override;


    //================================================ private variables ================================================
private:
    //void privateFunction();

//================================================ private functions ================================================
private:

};

#endif