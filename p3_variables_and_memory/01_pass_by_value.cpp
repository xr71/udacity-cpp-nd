#include <iostream>

void AddTwo(int val)
{
    val += 2;
}

int main(void)
{
    int val = 0;
    AddTwo(val);

    std::cout << val << std::endl;
}
