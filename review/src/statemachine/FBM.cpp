#include "FBM.h"
#include "RuheModus.h"
#include <iostream>
#include "memory_utils.h"

#ifdef ENABLE_STATE_TESTING
#include "BetriebsModus.h"
#include "ServiceModus.h"
#endif

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

#ifdef ENABLE_STATE_TESTING
bool FBM::isInRuheModus() const {
    return dynamic_cast<const RuheModus*>(currentstate_.get()) != nullptr;
}

bool FBM::isInBetriebsModus() const {
    return dynamic_cast<const BetriebsModus*>(currentstate_.get()) != nullptr;
}

bool FBM::isInServiceModus() const {
    return dynamic_cast<const ServiceModus*>(currentstate_.get()) != nullptr;
}
#endif