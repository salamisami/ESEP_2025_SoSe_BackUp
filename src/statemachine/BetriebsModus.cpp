#include "BetriebsModus.h"
#include "ServiceModus.h"
#include "FBM.h"
#include <iostream>

BetriebsModus::BetriebsModus(FBM* context) {
    context_ = context;
}

void BetriebsModus::enter() {
    std::cout << "Entering BetriebsModus - solid green\n";
    // Turn on solid green light
}

void BetriebsModus::handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) {
    // Behavior not specified in diagram
    std::cout << "Button start up in BetriebsModus\n";
}

void BetriebsModus::handleButtonStop() {
    std::cout << "Transition to ServiceModus\n";
    context_->transitionTo(std::make_unique<ServiceModus>(context_));
}