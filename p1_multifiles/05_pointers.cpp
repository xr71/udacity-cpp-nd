#include <iostream>
#include <vector>

using std::vector;


void AddOne(int *);
int* AddOnePtr(int &);

int main(void)
{
    int i = 5;
    int j = 6;

    std::cout << "the memory address of i is: " << &i << std::endl;
    std::cout << "the memory address of j is: " << &j << std::endl;

    /*
     *
     * At this point, you might be wondering why the same symbol & can be used
     * to both access memory addresses and, as you've seen before, pass
     * references into a function. This is a great thing to wonder about.
     * The overloading of the ampersand symbol & and the * symbol probably
     * contribute to much of the confusion around pointers.

     * The symbols & and * have a different meaning,
     * depending on which side of an equation they appear.

     * This is extremely important to remember. For the & symbol,
     * if it appears on the left side of an equation
     * (e.g. when declaring a variable), it means that the variable is
     * declared as a reference. If the & appears on the right side of an
     * equation, or before a previously defined variable, it is used to return
     * a memory address, as in the example above.
     *
    */

    // for example, if we want to store the address of the var i from above
    int *ptr_i = &i;
    std::cout << "the variable containing the address to i is: " << ptr_i << std::endl;

    // Once you have a pointer, you may want to retrieve the object it is
    // pointing to. In this case, the `*` symbol can be used again. This time,
    // however, it will appear on the right hand side of an equation or in
    // front of an already-defined variable, so the meaning is different.
    // In this case, it is called the "dereferencing operator", and it returns
    // the object being pointed to.

    std::cout << "the value that the pointer address of i is: " << *ptr_i << std::endl;


    // we can also create pointers of different types
    vector<int> v = {1,2,3,4};
    vector<int> *ptr_v = &v;
    std::cout << "we have a vector address that points a vector v: " << std::endl;
    std::cout << ptr_v << std::endl;
    std::cout << "the first element of this vector (*ptr_v)[0] is: " << (*ptr_v)[0] << std::endl;


    // we can modify a value directly by passing a pointer to a function
    std::cout << std::endl;
    i = 10;
    // we a pointer to i called ptr_i
    AddOne(ptr_i);
    std::cout << *ptr_i << std::endl;


    // we can do the same by returning a pointer;
    i = 10;
    int* ptr_i2 = AddOnePtr(i);
    std::cout << *ptr_i2 << std::endl;

}


void AddOne(int *num)
{

    // When using pointers with functions, some care should be taken.
    // If a pointer is passed to a function and then assigned to a variable
    // in the function that goes out of scope after the function finishes
    // executing, then the pointer will have undefined behavior at that point -
    // the memory it is pointing to might be overwritten by other parts of
    // the program.
    (*num)++;
}

int* AddOnePtr(int &j)
{
    // we can also use a function to return a pointer
    j++;
    return &j;
}
