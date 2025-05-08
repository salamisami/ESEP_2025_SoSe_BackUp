#ifndef IFBMSTATE_H
#define IFBMSTATE_H

#pragma once

#include <memory>

class FBM;

class IFBMState
{
public:
    virutal ~IFBMState() = default;
    virtual void enter() = 0;
    virutal void handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) = 0;
    virtual void handleButtonStop() = 0;

protected:
    FBM *context_;
}
#endif IFBMSTATE_H