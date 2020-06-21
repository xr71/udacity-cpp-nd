#include <iostream>

class ExclusiveCopy
{
private:
    int *_myInt;

public:
    ExclusiveCopy()
    {
        _myInt = (int *)malloc(sizeof(int));
        std::cout << "resource allocated" << std::endl;
    }
    ~ExclusiveCopy()
    {
        if (_myInt != nullptr)
        {
            free(_myInt);
            std::cout << "resource freed" << std::endl;
        }
    }

    // copy operators, one is constructor and one is assignment
    ExclusiveCopy(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
    }
    ExclusiveCopy &operator=(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
        return *this;
    }

    int GetInt() { return *_myInt; }
    void GetPtr() { std::cout << _myInt << std::endl; }
    void SetInt() { *_myInt = 42; }
};

int main()
{
    ExclusiveCopy source;
    source.SetInt();
    std::cout << source.GetInt() << std::endl;
    source.GetPtr();

    ExclusiveCopy destination(source);
    std::cout << destination.GetInt() << std::endl;
    destination.GetPtr();

    ExclusiveCopy anothercopy = destination;
    std::cout << anothercopy.GetInt() << std::endl;
    anothercopy.GetPtr();

    // finally, when we go out of scope of main, we free up *_myInt;
    return 0;
}
