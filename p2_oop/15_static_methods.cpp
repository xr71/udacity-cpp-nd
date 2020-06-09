#include <iostream>
#include <string>
#include <cassert>


/*
In addition to static member variables, C++ supports static member functions 
(or "methods"). Just like static member variables, static member functions 
are instance-independent: they belong to the class, not to any particular 
instance of the class.

One corollary to this is that we can method invoke a static member 
function without ever creating an instance of the class.
*/


class Sphere
{
  public:
    Sphere(int radius) : radius_(radius) {}
    static float constexpr pi_{3.14159};
    static float Volume(int radius)
    {
        return radius * radius * radius * pi_ * 4.0 / 3.0;
    }

  private:
    int radius_;
};


int main(void)
{
    std::cout << Sphere::Volume(5);
}