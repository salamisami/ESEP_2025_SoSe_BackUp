#ifndef IDLE_H
#define IDLE_H
#pragma once

#include "State.h"
#include "Traffic_Green_On_Slow.h"

class Idle : public State {
    //============================================ contructors & destructors ============================================
public:
    Idle(ContextData* data, State* previousState = nullptr);
    virtual ~Idle();

    //================================================ public functions ================================================
public:
    State* button_start_pressed() override;
    State* button_start_released() override;

    void entry() override;
    void exit() override;


    //================================================ private variables ================================================
private:
    //void privateFunction();

//================================================ private functions ================================================
private:
    State* subState;

};

#endif