#include <iostream>
#include "./inc/HelloWorld.h"

int main()
{
	IHelloWorld *hello = new HelloWorld();
	hello.method1();
}