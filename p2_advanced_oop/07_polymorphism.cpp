#include <ctime>
#include <iostream>

// to have many forms

/*
 * In the context of object-oriented programming, polymorphism)
 * describes a paradigm in which a function may behave differently
 * depending on how it is called. In particular, the function
 * will perform differently based on its inputs.
 *
 *
 *
 * In C++, you can write two (or more) versions of a function with the
 * same name. This is called "overloading". Overloading requires that
 * we leave the function name the same, but we modify the function
 * signature. For example, we might define the same function name
 * with multiple different configurations of input arguments.
 *
*/


// example

class Date {
public:
    Date(int day, int month, int year) : day_(day), month_(month), year_(year) {}
    Date(int day, int month) : day_(day), month_(month)  // automatically sets the Date to the current year
    {
        time_t t = time(NULL);
        tm* timePtr = localtime(&t);
        year_ = timePtr->tm_year;
    }

private:
    int day_;
    int month_;
    int year_;
};


// overloading can exist outside of classes as well

void hello()
{
    std::cout << "Hello, World!\n";
}

class Human {};

void hello(Human human)
{
    std::cout << "Hello, Human!\n";
}

class Dog {};
class Cat {};

void hello(Cat cat)
{
    std::cout << "Hello, Cat!\n";
}

void hello(Dog dog)
{
    std::cout << "Hello, Dog!\n";
}

int main(void)
{

    hello();

    Human h;

    hello(h);

    hello(Dog());
    hello(Cat());
}
