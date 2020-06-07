#include <iostream>
#include <string>

/*
 * Initializer lists initialize member variables to specific values, just
 * before the class constructor runs. This initialization ensures that class
 * members are automatically initialized when an instance of the class is
 * created.
 *
*/

// IMPORTANT NOTE
/*
 * In general, prefer initialization to assignment. Initialization sets the
 * value as soon as the object exists, whereas assignment sets the value only
 * after the object comes into being. This means that assignment creates and
 * opportunity to accidentally use a variable before its value is set.
 *
*/


// practice
class Person
{
    public:
        Person(std::string n);
        std::string getName() { return name; }
        void setName(std::string name);

    private:
        std::string name;
};

void Person::setName(std::string name)
{
    Person::name = name;
}

// constructor
Person::Person(std::string n) : name(n)
{

}

/*
 * Initializer lists exist for a number of reasons. First, the compiler can
 * optimize initialization faster from an initialization list than from
 * within the constructor.
 *
 * A second reason is a bit of a technical paradox. If you have a const
 * class attribute, you can only initialize it using an initialization list.
 * Otherwise, you would violate the const keyword simply by initializing
 * the member in the constructor!
 *
 * The third reason is that attributes defined as references must use
 * initialization lists.
*/

int main(void)
{
    Person bob("Bob");
    std::cout << bob.getName() << std::endl;

    bob.setName("Robert");
    std::cout << "Now I am " << bob.getName() << std::endl;
}



