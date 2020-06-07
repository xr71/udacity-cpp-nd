#include <iostream>
#include <ostream>

/*
 * C++ allows different identifiers (variable and function names) to have the
 * same name, as long as they have different scope.
 *
 * ::
 * is the scope resolution operator. We can use this operator to specify
 * which namespace or class to search in order to resolve an identifier.
 *
 * Class
 * Each class provides its own scope. We can use the scope resolution
 * operator to specify identifiers from a class.
 *
 * This becomes particularly useful if we want to separate class declaration
 * from class definition
 *
*/

class Date {
public:
    int Day() const { return day;  }
    void Day(int day);  // Declare member function Date::Day().

    int Month() const { return month;  }
    void Month(int month);

    int Year() const { return year;  }
    void Year(int year);

private:
    int day{1};
    int month{1};
    int year{0};
};

// Define member function Date::Day().
void Date::Day(int day) 
{
   if (day >= 1 && day <= 31) Date::day = day;
}
void Date::Month(int month)
{
    if (month >= 1 && month <= 12) Date::month = month;
}
void Date::Year(int year)
{
    Date::year = year;
}


// namespaces
namespace English
{
    void Hello()
    {
        std::cout << "Hello!" << std::endl;
    }
}

namespace Spanish
{
    void Hello()
    {
        std::cout << "Hola!" << std::endl;
    }
}

int main(void)
{
    Date newdate;
    newdate.Year(2020);
    newdate.Month(6);
    newdate.Day(8);

    std::cout << newdate.Day() << std::endl;
    std::cout << newdate.Month() << std::endl;
    std::cout << newdate.Year() << std::endl;


    // test namespaces
    English::Hello();
    Spanish::Hello();
}
