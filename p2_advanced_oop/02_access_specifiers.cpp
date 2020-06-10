#include <iostream>
#include <string>


/*
 * Just as access specifiers (i.e. public, protected,
 * and private) define which class members
 * users can access, the same access modifiers
 * also define which class members users of a derived


 * Public inheritance: the public and protected
 * members of the base class listed after the
 * specifier keep their member access in the
 * derived class

 * Protected inheritance: the public and protected
 * members of the base class listed after the
 * specifier are protected members of the
 * derived class

 * Private inheritance: the public and protected
 * members of the base class listed after the
 * specifier are private members of the
 * derived class
*/


class Mammal
{
  public:
    void Talk()
    {
        std::cout << "Hello\n";
    }
};

class Human : public Mammal
{
  public:
    void Talk(std::string content)
    {
        std::cout << content << std::endl;
    }
};

class Baby : private Human
{
  public:
    void Cry()
    {
        Talk("Waaa");
    }
};

int main(void)
{
    Human h;
    h.Talk("Hello I am human");

    Baby b;
    // this will fail: b.Talk();
    b.Cry();
}
