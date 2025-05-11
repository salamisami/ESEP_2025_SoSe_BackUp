#ifndef BETRIEBSMODUS_H
#define BETRIEBSMODUS_H

#include "IFBMState.h"

class BetriebsModus : public IFBMState
{
public:
    explicit BetriebsModus(FBM *context);
    void enter() override;
    void handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) override;
    void handleButtonStop() override;
};

#endif