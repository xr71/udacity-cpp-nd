#include <iostream>

/*
 * "Overriding" a function occurs when:
 *
 * A base class declares a virtual function.
 * A derived class overrides that virtual function by defining its own implementation with an identical function signature (i.e. the same function name and argument types).
 * class Animal {
 * public:
 *   virtual std::string Talk() const = 0;
 *   };
 *
 *   class Cat {
 *   public:
 *     std::string Talk() const { return std::string("Meow");  }
 *     };
*     In this example, Animal exposes a virtual function: Talk(), but does
*     not define it. Because Animal::Talk() is undefined, it is called a
*     pure virtual function, as opposed to an ordinary (impure? ;))
*     virtual function.
*
*     Furthermore, because Animal contains a pure virtual function,
*     the user cannot instantiate an object of type Animal.
*     This makes Animal an abstract class.
 *
 *
*/

class Animal
{
    public:
         virtual std::string Talk() const = 0;

};

class Cat
{
    public:
         std::string Talk() const { return std::string("Meow");  }

};

class Dog
{
    public:
        std::string Talk() const { return std::string("Woof"); }
};


int main(void)
{
    Dog d;
    std::cout << d.Talk() << std::endl;
}
