#include <iostream>

void AddThree(int *p)
{
    // we create a copy of the pointer

    // deref that specific pointer and add 3
    *p += 3;
}

int main(void)
{
    int val = 0;
    AddThree(&val);

    std::cout << val << std::endl;
}
