//
// Created by xuren on 5/31/20.
//

#include <iostream>

int main()
{
    int p = 123;

    std::cout << p << std::endl;
    std::cout << &p << std::endl;
    std::cout << std::endl;


    int *pp;
    *pp = 456;
    // pp is a pointer, so it just prints out the pinter address
    std::cout << pp << std::endl;
    // use * to look at the actual value inside;
    std::cout << *pp << std::endl;
}