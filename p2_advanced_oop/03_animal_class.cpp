#include <iostream>
#include <string>


class Animal
{
  public:
    std::string color;
    std::string name;
    int age;
};

class Snake : public Animal
{
  public:
    int length;
    void MakeSound() { std::cout << "Hisssssssssss\n"; }
};

class Cat : public Animal
{
  public:
    int height;
    void MakeSound() { std::cout << "Meowwwwww\n"; }
};

int main(void)
{
    Snake s;
    s.color = "Green";
    s.name = "Lizzy";
    s.age = 2;
    std::cout << s.name << " the " << s.color << " snake makes the sound ";
    s.MakeSound();

    Cat c;
    c.color = "White";
    c.name = "Ozzy";
    c.age = 4;
    std::cout << c.name << " the " << c.color << " cat makes the sound ";
    c.MakeSound();
}
