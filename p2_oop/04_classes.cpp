#include <iostream>
#include <vector>
#include <cassert>

// Classes, like structures, provide a way for C++ programmers to
// aggregate data together in a way that makes sense in the context
// of a specific program. By convention, programmers use structures
// when member variables are independent of each other, and use
// classes when member variables are related by an "invariant".

//An "invariant" is a rule that limits the values of member variables.
// For example, in a Date class, an invariant would specify that the
// member variable day cannot be less than 0.
// Another invariant would specify that the value of day cannot
// exceed 28, 29, 30, or 31, depending on the month and year.
// Yet another invariant would limit the value of month to the range of 1 to 12.

class Date
{
public:
    int getDay() { return day; }
    void setDay(int d)
    {
        if (d > 0 && d < 32)
        {
            day = d;
        }
        else
        {
            day = 0;
        }
    }

private:
    int day{0};
    int month{0};
    int year{0};
};

int main(void)
{
    Date newdate;
    std::cout << newdate.getDay() << std::endl;
    newdate.setDay(10);
    std::cout << newdate.getDay() << std::endl;
    newdate.setDay(-7);
    std::cout << newdate.getDay() << std::endl;
}