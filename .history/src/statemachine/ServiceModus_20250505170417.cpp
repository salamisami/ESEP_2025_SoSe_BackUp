#include "../inc/ServiceModus.h"
#include "../inc/RuheModus.h"
#include "FBM.h"
#include <iostream>

RestMode::RestMode(TrafficLight *context)
{
    context_ = context;
}

void RestMode::enter()
{
    std::cout << "Entering Rest Mode - 0.5Hz blinking\n";
    context_->startBlinkingThread(0.5);
}

void RestMode::handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning)
{
    if (pressedLong && !hasErrorOrWarning)
    {
        std::cout << "Transition to Operation Mode\n";
        context_->transitionTo(std::make_unique<OperationMode>(context_));
    }
    else
    {
        std::cout << "Short press or error/warning - staying in Rest Mode\n";
    }
}

void RestMode::handleButtonStop()
{
}