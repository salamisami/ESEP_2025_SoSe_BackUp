#ifndef IHelloWorld_H
#define IHelloWorld_H

#pragma once

class IHelloWorld
{
public:
    virtual ~IHelloWorld() = default;
    virtual void method1() = 0;
};
#endif
