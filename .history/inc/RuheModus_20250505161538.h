#ifndef RUHEMODUS_H
#define RUHEMODUS_H

#include "IFBMState.h"

class RuheModus : public IFBMState
{
public:
    explicit RuheModus(FBM *context);
    void enter() override;
    void handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) override;
    void handleButtonStop() override;
};

#endif