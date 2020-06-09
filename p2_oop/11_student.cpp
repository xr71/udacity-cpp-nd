#include <iostream>
#include <string>
#include <cassert>


class Student
{
public:
    Student(std::string name, int grade, float gpa)
        : name_(name), grade_(grade), gpa_(gpa) {}

    // accessors
    std::string Name() const { return name_; }
    int Grade() const { return grade_; }
    float GPA() const { return gpa_; }

    // mutators
    void Grade(int n)
    {
        if (n < 0 || n > 12)
        {
            throw std::invalid_argument("grade is out of bounds");
        }
        else
        {
            grade_ = n;
        }
    }

private:
    std::string name_;
    int grade_;
    float gpa_;
};


int main(void)
{

    Student billy = Student("Billy Joe", 10, 3.94);
    std::cout << billy.Name() << " is in the " << billy.Grade() << " grade and has gpa of " << billy.GPA() << std::endl;

    bool caught{false};
    try
    {
        billy.Grade(100);
    }
    catch(...)
    {
        caught = true;
    }
    assert(caught);

    // billy's grade should still be 10
    std::cout << billy.Grade() << std::endl;
}
