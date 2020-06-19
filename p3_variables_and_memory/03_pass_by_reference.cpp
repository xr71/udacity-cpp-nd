#include <iostream>

void AddFour(int &val)
{
    val += 4;
}

int main(void)
{
    int val = 0;
    AddFour(val);

    std::cout << val << std::endl;
}
