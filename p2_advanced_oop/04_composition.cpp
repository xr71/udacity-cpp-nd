#include <iostream>
#include <cmath>

/*
 * Composition involves constructing ("composing") classes from other
 * classes, instead of inheriting traits from a parent class.

A common way to distinguish "composition" from "inheritance" is to think
about what an object can do, rather than what it is. This is often
expressed as "has a" versus "is a".

From the standpoint of composition, a cat "has a" head and "has a" set of
paws and "has a" tail.

From the standpoint of inheritance, a cat "is a" mammal.

There is no hard and fast rule about when to prefer composition over
inheritance. In general, if a class needs only extend a small amount of
functionality beyond what is already offered by another class, it makes
sense to inherit from that other class. However, if a class needs to contain
functionality from a variety of otherwise unrelated classes, it makes
sense to compose the class from those other classes.
*/



// example
#define PI 3.14159;


struct LineSegment
{
  public:
    double length;
};

class Circle
{
  public:
    Circle(LineSegment &radius);
    double Area();

  private:
    LineSegment &radius_;
};

// constructor
Circle::Circle(LineSegment &radius) : radius_(radius) {}

// define function for Area
double Circle::Area()
{
    return pow(Circle::radius_.length, 2) * PI;
}


int main(void)
{
    // create a line segment that is a radius with a length of 3
    LineSegment radius {3};
    std::cout << radius.length << std::endl;

    // create a circle with this radius length;
    Circle circle(radius);
    std::cout << "The area of the circle is: " << circle.Area() << std::endl;
}
