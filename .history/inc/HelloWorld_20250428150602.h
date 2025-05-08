#ifndef HelloWorld_H
#define HelloWorld_H
#pragma once
#include "IHelloWorld.h"

class HelloWorld : public IHellowWorld
{
public:
    void method1() const override;
}
#endif