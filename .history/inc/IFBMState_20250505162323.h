#ifndef IFBMSTATE_H
#define IFBMSTATE_H

#pragma once

#include <memory>

class FBM;

class IFBMState
{
public:
    virtual ~IFBMState() = default;
    virtual void enter() = 0;
    virtual void handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) = 0;
    virtual void handleButtonStop() = 0;

protected:
    FBM *context_;
};
#endif