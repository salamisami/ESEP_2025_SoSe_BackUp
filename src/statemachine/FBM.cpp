#include "FBM.h"
#include "RuheModus.h"
#include <iostream>
#include "memory_utils.h"

FBM::FBM()
{
    transitionTo(make_unique<RuheModus>(this));
}

FBM::~FBM() {
    // Add cleanup code if needed (e.g., freeing resources)
}

void FBM::transitionTo(std::unique_ptr<IFBMState> state)
{
    stopBlinkingThread();
    currentstate_ = std::move(state);
    currentstate_->enter();
}

void FBM::buttonStartUp(bool pressedLong, bool hasErrorOrWarning)
{
    currentstate_->handleButtonStartUp(pressedLong, hasErrorOrWarning);
}

void FBM::buttonStop()
{
    currentstate_->handleButtonStop();
}

void FBM::startBlinkingThread(double frequency)
{
}

void FBM::stopBlinkingThread()
{
}
