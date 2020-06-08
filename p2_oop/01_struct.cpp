#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// we can start with STRUCTS - these provide data structures to a user defined type
struct Date
{
    int day;
    int month;
    int year;
};
// this allows us to aggregate related data into a single var

int main()
{
    Date date;
    date.day = 8;
    date.month = 6;
    date.year = 2020;

    std::cout << date.year << " - " << date.month << " - " << date.day << std::endl;
}