#include "../inc/FBM.h"
#include "../inc/RuheModus.h"
#include <iostream>

FBM::FBM()
{
    transitionTo(std::make_unique<RuheModus>(this));
}