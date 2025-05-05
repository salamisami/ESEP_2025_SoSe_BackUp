#include "../inc/RuheModus.h"
#include "../inc/BetriebsModus.h"
#include "FBM.h"
#include <iostream>

RuheModus::RestMode(TrafficLight *context)
{
    context_ = context;
}

void RuheModus::enter()
{
    std::cout << "Entering Rest Mode - 0.5Hz blinking\n";
    context_->startBlinkingThread(0.5);
}

void RuheModus::handleButtonStartUp(bool pressedLong, bool hasErrorOrWarning)
{
    if (pressedLong && !hasErrorOrWarning)
    {
        std::cout << "Transition to Operation Mode\n";
        context_->transitionTo(std::make_unique<BetriebsModus>(context_));
    }
    else
    {
        std::cout << "Short press or error/warning - staying in Rest Mode\n";
    }
}

void RuheModus::handleButtonStop()
{
}