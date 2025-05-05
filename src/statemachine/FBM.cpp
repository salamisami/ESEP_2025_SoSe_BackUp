#include "../inc/FBM.h"
#include "../inc/RuheModus.h"
#include <iostream>

FBM::FBM()
{
    transitionTo(std::make_unique<RuheModus>(this));
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