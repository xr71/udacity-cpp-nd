#include <iostream>
#include <stdlib.h>
#include <stdio.h>

struct MyStruct {
    int i;
    double d;
    char a[5];
};

int main(void)
{

    // we have to cast it to a type in order to know the size and end of memory allocation

    int *p = (int*)malloc(sizeof(int));

    std::cout << p << " has the value " << *p << std::endl;

    MyStruct *sp = (MyStruct*)calloc(4,sizeof(MyStruct));
    sp[0].i = 1; sp[0].d = 3.14159; sp[0].a[0] = 'a';
}
