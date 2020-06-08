#include <iostream>

class Date
{
public:
    Date(int d, int m, int y)
    {
        setDay(d);
        setMonth(m);
        setYear(y);
    }

    int getDay() { return day; }
    void setDay(int d)
    {
        if (d >= 1 && d <= 31)
        {
            day = d;
        }
    }

    int getMonth() { return month; }
    void setMonth(int m)
    {
        if (m >= 1 && m <= 12)
        {
            month = m;
        }
    }

    int getYear() { return year; }
    void setYear(int y)
    {
        year = y;
    }

private:
    int day;
    int month;
    int year;
};

/*
Default Constructor
A class object is always initialized by calling a constructor. 
That might lead you to wonder how it is possible to initialize 
a class or structure that does not define any constructor at all.

For example:

class Date { 
  int day{1};
  int month{1};
  int year{0};
};

We can initialize an object of this class, even though 
this class does not explicitly define a constructor.
*/

int main(void)
{
    Date newdate(8, 6, 2020);
    std::cout << newdate.getYear() << " - " << newdate.getMonth() << " - " << newdate.getDay() << std::endl;
}