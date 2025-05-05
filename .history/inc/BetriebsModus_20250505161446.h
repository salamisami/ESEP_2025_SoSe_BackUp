#ifndef BETRIEBSMODUS_H
#define BETRIEBSMODUS_H

#include "IFBMState.h"

class OperationMode : public IFBMState
{
public:
    explicit OperationMode(FBM *context);
    void enter() override;
    void handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) override;
    void handleButtonStop() override;
};

#endif