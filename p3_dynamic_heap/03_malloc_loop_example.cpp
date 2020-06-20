#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main(void)
{
    int i = 10000000;

    float sum = 0.0;

    for (int k = 0; k < i; k++)
    {
        sum = sum + k;
    }

    std::cout << sum << std::endl;
}
