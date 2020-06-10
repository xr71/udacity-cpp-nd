#include <iostream>
#include <vector>
#include <assert.h>

/*
 * Deduction occurs when you instantiate an object without explicitly
 * identifying the types. Instead, the compiler "deduces" the types.
 * This can be helpful for writing code that is generic and can handle a
 *
 */


// in C++ 17, we can actually call vector without a type
//


template <typename T> T average(T a, T b) { return (a+b)/2;  }

int main(void)
{
    // this will work only if compiled with c++17
    std::vector v = {1, 2, 3, 4};
    std::cout << v.size() << std::endl;

    // we can call average without explicit types
    std::cout << average(2.0, 4.0) << std::endl;
}
