#ifndef SERVICEMODUS_H
#define SERVICEMODUS_H

#include "IFBMState.h"

class ServiceModus : public IFBMState
{
public:
    explicit ServiceModus(FBM *context);
    void enter() override;
    void handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) override;
    void handleButtonStop() override;
};

#endif