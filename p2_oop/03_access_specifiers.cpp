#include <iostream>

// by default, structs members are public

struct Date
{
    // in this case, we will need setters and getters
public:
    int getDay()
    {
        return day;
    }

    void setDay(int d)
    {
        day = d;
    }

private:
    int day{1};
    int month{1};
    int year{2000};
};

int main(void)
{
    Date newdate;
    std::cout << newdate.getDay() << std::endl;
    newdate.setDay(20);
    std::cout << newdate.getDay() << std::endl;
}