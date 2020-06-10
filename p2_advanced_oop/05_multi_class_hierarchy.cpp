#include <iostream>

/*
 * Multi-level inheritance is term used for chained classes in an inheritance
 * tree. Have a look at the example in the notebook below to get a feel
 * for multi-level inheritance.
 *
*/


class Vehicle
{
    public:
        int wheels;
};

class Car : public Vehicle
{
    public:
        int wheels{4};
};

class Sedan : public Car
{
    public:
        int seats{4};
        bool trunk{true};
};

int main(void)
{
    Sedan corolla;

    std::cout << corolla.trunk << " " << corolla.seats << std::endl;
}

