#include <iostream>
#include <vector>
#include <string>

/*
 *
 * INHERITANCE
 *
 * In our everyday life, we tend to divide things into groups, based on
 * their shared characteristics. Here are some groups that you have probably
 * used yourself: electronics, tools, vehicles, or plants.
 *
 * Sometimes these groups have hierarchies. For example, computers and
 * smartphones are both types of electronics, but computers and
 * smartphones are also groups in and of themselves. You can imagine a tree
 * with "electronics" at the top, and "computers" and "smartphones" each as
 * children of the "electronics" node.
 *
*/


// example

class Mammal
{
  public:
    void Talk() const { std::cout << "Hello\n"; }
};

class Human : public Mammal
{
  public:
    void Walk() const { std::cout << "I can walk\n"; }
};

// more example

class Vehicle {
public:
    int wheels = 0;
    std::string color = "blue";

    void Print() const
    {
        std::cout << "This " << color << " vehicle has " << wheels << " wheels!\n";
    }
};

class Car : public Vehicle {
public:
    bool sunroof = false;
};

class Bicycle : public Vehicle {
public:
    bool kickstand = true;
};

int main(void)
{
    Mammal m;
    Human h;

    m.Talk();
    h.Talk();
    h.Walk();


    Car c;
    Bicycle b;

    // access parent members
    c.wheels = 4;
    b.wheels = 2;

    c.Print();
    b.Print();
}
