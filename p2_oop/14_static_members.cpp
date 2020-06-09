#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


// Class members can be declared static, which means that the member 
// belongs to the entire class, instead of to a specific instance of the class. 
// More specifically, a static member is created only once and then 
// shared by all instances (i.e. objects) of the class. 
// That means that if the static member gets changed, either 
// by a user of the class or within a member function of the class itself, 
// then all members of the class will see that change the next time they 
// access the static member.


/*
static members are declared within their class (often in a header file) but 
in most cases they must be defined within the global scope. 
That's because memory is allocated for static variables immediately when 
the program begins, at the same time any global variables are initialized.
*/


class Sphere 
{
  public:
    Sphere(int radius) : radius_(radius) {}
    static float constexpr pi_{3.14159};

  private:
    int radius_;
};


int main(void)
{
  std::cout << Sphere::pi_ << std::endl;

  // with const we do not accidentally change
  // Sphere::pi_ = 3;
}