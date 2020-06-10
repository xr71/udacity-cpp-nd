#include <iostream>

class Car
{
    public:
        void Drive() { std::cout << "I can drive!\n"; }
};

class Boat
{
    public:
        void Cruise() { std::cout << "I can cruise!\n"; }
};

class AmphiCar : public Car, public Boat
{};


int main(void)
{
    AmphiCar duckcar;
    duckcar.Drive();
    duckcar.Cruise();
}


// NOTE
// multiple inheritance is tricky and can run into the diamond problem
// two base classes inerhit from an abstract class
// this is fine
// but what if a new class inherits from both classes that inherited from an
// abstract class
// this new class is now going to have two override methods - so which one to call?

// DIAMOND problem because the inheritance looks like a diamon
//                      ABSTRACT CLASS
//              OVERRIDE 1                 OVERRIDE 2
//                      New class that
//                      inherits from both
//
