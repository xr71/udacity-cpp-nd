#include <iostream>
#include <cassert>

// Generally, we want to avoid instantiating an object with undefined members.
// Ideally, we would like all members of an object to be in a valid state once
// the object is instantiated. We can change the values of the members later,
// but we want to avoid any situation in which the members are ever in an
// invalid state or undefined.
struct Date
{
    int day{1};
    int month{1};
    int year{2020};
};

int main()
{
    Date newdate;

    std::cout << newdate.year << newdate.month << newdate.day << std::endl;
}