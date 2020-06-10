#include <iostream>



/*
 *
 * Virtual functions are a polymorphic feature.
 * These functions are declared (and possibly defined) in a
 * base class, and can be overridden by derived classes.
 *
 *
 * A pure virtual function is a virtual function that the
 * base class declares but does not define.
 *
 *
*/

// example of pure virtual functions
class Shape
{
    public:
        Shape() {}
        virtual double Area() const = 0;
        virtual double Perimeter() const = 0;
};

/*
 * Virtual functions can be defined by derived classes, but
 * this is not required. However, if we mark the virtual
 * function with = 0 in the base class, then we are declaring the
 * function to be a pure virtual function. This means that the base class
 * does not define this function. A derived class must define this
 * function, or else the derived class will be abstract.
 *
*/


class Circle : public Shape
{
    public:
        Circle(int r) : radius(r) {}

        double Area() const override
        {
            return radius * radius * 3.14159;
        }
        double Perimeter() const override
        {
            return 2 * 3.14159 * radius;
        }

    private:
        int radius;
};

class Rectangle : public Shape
{
    public:
        Rectangle(int w, int h) : width(w), height(h) {}

        double Area() const override
        {
            return width * height;
        }
        double Perimeter() const override
        {
            return width * 2 + height * 2;
        }

    private:
        int width;
        int height;
};

int main(void)
{

    Circle c{5};
    std::cout << c.Area() << std::endl;

    Rectangle r(4,4);
    std::cout << r.Area() << std::endl;
}
