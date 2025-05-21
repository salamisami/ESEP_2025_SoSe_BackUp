#include "ServiceModus.h"
#include "RuheModus.h"
#include "FBM.h"
#include <iostream>
#include "memory_utils.h"

ServiceModus::ServiceModus(FBM* context) {
    context_ = context;
}

void ServiceModus::enter() {
    std::cout << "Entering Servicemodus - 5Hz blinking\n";
    context_->startBlinkingThread(5.0);
}

void ServiceModus::handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning) {
    // Behavior not specified in diagram
    std::cout << "Button start up in Servicemodus\n";
}

void ServiceModus::handleButtonStop() {
    std::cout << "Transition to Ruhemodus\n";
    context_->transitionTo(make_unique<RuheModus>(context_));
}
