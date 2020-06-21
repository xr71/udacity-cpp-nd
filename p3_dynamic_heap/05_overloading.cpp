#include <iostream>
#include <stdlib.h>

class MyClass
{
    int _mymember;

public:
    MyClass()
    {
        std::cout << "2 Constructor is called\n";
    }

    ~MyClass()
    {
        std::cout << "3 Destructor is called\n";
    }

    void *operator new(size_t size)
    {

        void *p = malloc(size);

        std::cout << "1 new: Allocating " << size << " bytes of memory at " << p << std::endl;
        return p;
    }

    void operator delete(void *p)
    {
        std::cout << "4 delete: Memory is freed again " << std::endl;
        free(p);
    }
};

int main()
{
    MyClass *p = new MyClass();
    std::cout << p << std::endl;
    delete p;
}
