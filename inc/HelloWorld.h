#ifndef HelloWorld_H
#define HelloWorld_H
#pragma once
#include "IHelloWorld.h"

class HelloWorld : public IHelloWorld
{
public:
    void method1() override;
};
#endif
