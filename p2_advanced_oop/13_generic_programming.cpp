#include <iostream>

// a template that allows functions to work with many data types
// generalize the functions
//
// in this sense, the hierarchy disappears, and the input data types
// are parameterized -- generic programming


// template
// type T (generic)

/*
 * example
 * template <typename Type> Type Sum(Type a, Type b) { return a + b;  }
 *
 * int main() { std::cout << Sum<double>(20.0, 13.7) << "\n";  }
 *
 */


template <typename T>
T Max(T a, T b)
{
    return a>b ? a : b;
}

int main(void)
{
    std::cout << Max<double>(1.0, 5.0) << std::endl;
}
