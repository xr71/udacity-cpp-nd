#include <iostream>

void OuterFunction(int i);
void InnerFunction(int i);

int main()
{
    OuterFunction(5);
}

void OuterFunction(int i)
{
    InnerFunction(i);
}

void InnerFunction(int i)
{
    std::cout << "the value of i is " << i << std::endl; 
}
