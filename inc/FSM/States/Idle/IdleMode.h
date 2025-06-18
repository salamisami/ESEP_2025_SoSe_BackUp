#ifndef IDLEMODE_H
#define IDLEMODE_H
#pragma once

#include "HState.h"
#include "IdleIM.h"

class IdleMode : public HState {
    //============================================ constructors & destructors ============================================
public:
    IdleMode(ContextData* data);
    virtual ~IdleMode();

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