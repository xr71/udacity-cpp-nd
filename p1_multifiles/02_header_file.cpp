#include "header_example.h"
#include <iostream>

void OuterFunction(int i)
{
    InnerFunction(i);
}

void InnerFunction(int i)
{

    std::cout << "the value of i is " << i << std::endl;
}

int main(void)
{
    OuterFunction(5);
}

