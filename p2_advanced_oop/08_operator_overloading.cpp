#include <iostream>
#include <cmath>


// operator overlaoding allows us to design our own logic
// for ascii operations on custom class types

// use the operator keyword in the function signature
// a good use case may be something like vector addition


class Point
{
    public:
        Point(int x=0, int y=0) : x_(x), y_(y) {}

        // we need to define our own addition operator for two Points
        Point operator+(const Point &addend)
        {
            // a new point to be returned
            Point sum;

            sum.x_ = x_ + addend.x_;
            sum.y_ = y_ + addend.y_;

            return sum;
        }

        int X() { return x_; }
        int Y() { return y_; }

    private:
        int x_{0};
        int y_{0};
};


int main(void)
{
    Point firstpt {1,3};
    Point secondpt {4, 0};

    Point thirdpt = firstpt + secondpt;

    std::cout << thirdpt.X() << ", " << thirdpt.Y() << std::endl;
}
