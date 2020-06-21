# The HEAP

### Properties of Heap Memory

Heap memory, also know as dynamic memory , is an important resource available to programs (and programmers) to store data.
The beauty of C++ is that it is very hardware oriented, so we can make a lot of optimizations down tothe RAM level. However, this also makes for more room for errors and even harder to locate and debug these errors at times.

As mentioned earlier, the heap memory grows upwards while the stack grows in the opposite direction. We have seen in the last lesson that the automatic stack memory shrinks and grows with each function call and local variable. As soon as the scope of a variable is left, it is automatically deallocated and the stack pointer is shifted upwards accordingly.

Heap memory is different in many ways: The programmer can request the allocation of memory by issuing a command such as malloc or new (more on that shortly). This block of memory will remain allocated until the programmer explicitly issues a command such as free or delete. The huge advantage of heap memory is the high degree of control a programmer can exert, albeit at the price of greater responsibility since memory on the heap must be actively managed.

Properties:

- can be allocated in arbitrary scope
- as long as the address is returned to the caller, it can be used
- local variables on the stack are allocated at compile time, so this is not optimal for strings or arrays for which their lengths we do not know. However, with Heap, variables are allocated at run time, so the var length can be tailored to what is needed by the user
- heap memory is only constrained by the virtual memory address space - but this can create memory leaks if not de-allocated properly
- unlike the stack, the heap is shared by threads, so concurrency needs to be accounted for, where several threads may compete for the same resources
- in the stack, the pointer is simply shifted upward or downward, but with heap memory allocation, and de-allocation, this can happen arbitarily since memory isn't sequential, and it depends on the lifetime of variables, so memory can become fragmented overtime, making it more difficult and expensive to manage

#### Memory Fragmentation

A classic symptom of memory fragmentation is that you try to allocate a large block and you can’t, even though you appear to have enough memory free. On systems with virtual memory however, this is less of a problem, because large allocations only need to be contiguous in virtual address space, not in physical address space.

When memory is heavily fragmented however, memory allocations will likely take longer because the memory allocator has to do more work to find a suitable space for the new object.

#### Using Malloc and Free

So far we only considered primitive data types, whose storage space requirement was already fixed at compile time and could be scheduled with the building of the program executable. However, it is not always possible to plan the memory requirements exactly in advance, and it is inefficient to reserve the maximum memory space each time just to be on the safe side. C and C++ offer the option to reserve memory areas during the program execution, i.e. at runtime. It is important that the reserved memory areas are released again at the "appropriate point" to avoid memory leaks. It is one of the major challenges in memory management to always locate this "appropriate point" though.

To allocate dynamic memory on the heap means to make a contiguous memory area accessible to the program at runtime and to mark this memory as occupied so that no one else can write there by mistake.

To reserve memory on the heap, one of the two functions malloc (stands for Memory Allocation) or calloc (stands for Cleared Memory Allocation) is used. The header file stdlib.h or malloc.h must be included to use the functions.

malloc is used to dynamically allocate a single large block of memory with the specified size. It returns a pointer of type void which can be cast into a pointer of any form.

calloc is used to dynamically allocate the specified number of blocks of memory of the specified type. It initializes each block with a default value '0'.

Both functions return a pointer of type void which can be cast into a pointer of any form. If the space for the allocation is insufficient, a NULL pointer is returned.

#### Malloc for arrays and strcuts

```c++
    int *p = (int*)malloc(3*sizeof(int));
    p[0] = 1; p[1] = 2; p[2] = 3;
    printf("address=%p, second value=%d\n", p, p[1]);
```

and for non-primitive types

```c++
struct MyStruct {
    int i;
    double d;
    char a[5];
};

MyStruct *p = (MyStruct*)calloc(4,sizeof(MyStruct));
p[0].i = 1; p[0].d = 3.14159; p[0].a[0] = 'a';

```

#### Freeing Up Memory

If memory has been reserved, it should also be released as soon as it is no longer needed. If memory is reserved regularly without releasing it again, the memory capacity may be exhausted at some point. If the RAM memory is completely used up, the data is swapped out to the hard disk, which slows down the computer significantly.

The free function releases the reserved memory area so that it can be used again or made available to other programs. To do this, the pointer pointing to the memory area to be freed is specified as a parameter for the function.

Considerations:

- free can only free memory that was reserved with malloc or calloc.
- free can only release memory that has not been released before. Releasing the same block of memory twice will result in an error.
- Memory allocated with malloc or calloc is not subject to the familiar rules of variables in their respective scopes. This means that they exist independently of block limits until they are released again or the program is terminated. However, the pointers which refer to such heap-allocated memory are created on the stack and thus only exist within a limited scope. As soon as the scope is left, the pointer variable will be lost - but not the heap memory it refers to.

#### New and Delete

Comparing `malloc` with `new`
The functions malloc and free are library function and represent the default way of allocating and deallocating memory in C. In C++, they are also part of the standard and can be used to allocate blocks of memory on the heap.

With the introduction of classes and object oriented programming in C++ however, memory allocation and deallocation has become more complex: When an object is created, its constructor needs to be called to allow for member initialization. Also, on object deletion, the destructor is called to free resources and to allow for programmer-defined clean-up tasks. For this reason, C++ introduces the operators new / delete, which represent the object-oriented counterpart to memory management with malloc / free.

If we were to create a C++ object with malloc, the constructor and destructor of such an object would not be called.

```c++
#include <stdlib.h>
#include <iostream>

class MyClass
{
private:
    int *_number;

public:
    MyClass()
    {
        std::cout << "Allocate memory\n";
        _number = (int *)malloc(sizeof(int));
    }
    ~MyClass()
    {
        std::cout << "Delete memory\n";
        free(_number);
    }
    void setNumber(int number)
    {
        *_number = number;
        std::cout << "Number: " << _number << " is the number " << *_number << "\n";
    }
};


int main()
{
    // allocate memory using malloc
    // comment these lines out to run the example below
//     MyClass *myClass = (MyClass *)malloc(sizeof(MyClass));
//     myClass->setNumber(42); // EXC_BAD_ACCESS
//     free(myClass);

	// allocate memory using new
    MyClass *myClass = new MyClass();
    myClass->setNumber(42); // works as expected
    delete myClass;

    return 0;
}
```

With malloc, the program crashes on calling the method setNumber, as no memory has been allocated for `_number` - because the constructor has not been called. Hence, an EXC_BAD_ACCESS error occurs, when trying to access the memory location to which `_number` is pointing.

In short:

- Constructors / Destructors, with new and delete they are called, but not with malloc and free
- Type safety: `malloc` returns a `void` pointer, this means that it needs to be cast properly (to the right data type, which is an object type here) before being used. This is not type safe, you can freely vary the pointer type without any warnings or errors from the compiler
- Overloading: malloc and free are functions defined in the std lib, so their behaviors cannot be changed easily, the `new` and `delete` operators can be overloaded by a class in order to include optional behaviors
- Remember to always call delete after new, failing to do so will cause the object to reside in memory until the program terminates at some point in the future, causing a _memory leak_

Consequences of calling new and delete

- New
  - memory is allocated to hold a new object of type CLASS
  - new object of type CLASS is constructed within the allocated memory by calling the constructor of that class
- Delete
  - the object of type CLASS is destroyed by calling its destructor
  - the memory which the object was placed in is deallocated

#### Performance with `placement new`

In some cases, it makes sense to separate memory allocation from object construction. Consider a case where we need to reconstruct an object several times. If we were to use the standard new/delete construct, memory would be allocated and freed unnecessarily as only the content of the memory block changes but not its size. By separating allocation from construction, we can get a significant performance increase.

C++ allows us to do this by using a construct called placement new: With placement new, we can pass a preallocated memory and construct an object at that memory location. Consider the following code:

```c++
void *memory = malloc(sizeof(MyClass));
MyClass *object = new (memory) MyClass;
```

The syntax new (memory) is denoted as placement new.

The difference to the "conventional" new we have been using so far is that that no memory is allocated. The call constructs an object and places it in the assigned memory location. There is however, no delete equivalent to placement new, so we have to call the destructor explicitly in this case instead of using delete as we would have done with a regular call to new:

```c++
object->~MyClass();
free(memory);
```

#### Overloading new and delete

One of the major advantages of new/delete over free/malloc is the possibility of overloading. While both malloc and free are function calls and thus can not be changed easily, new and delete are operators and can thus be overloaded to integrate customized functionality, if needed.

The syntax for overloading the new operator looks as follows:
`void* operator new(size_t size);`

The operator receives a parameter size of type size_t, which specifies the number of bytes of memory to be allocated. The return type of the overloaded new is a void pointer, which references the beginning of the block of allocated memory.

The syntax for overloading the delete operator looks as follows:
`void operator delete(void*);`

The operator takes a pointer to the object which is to be deleted. As opposed to new, the operator delete does not have a return value

We can also overload new and delete for arrays:

```c++
void* operator new[](size_t size);
void operator delete[](void*);
```

#### Reasons for overloading new and delete

Now that we have seen how to overload the new and delete operators, let us summarize the major scenarios where it makes sense to do this:

The overloaded new operator function allows to add additional parameters. Therefore, a class can have multiple overloaded new operator functions. This gives the programmer more flexibility in customizing the memory allocation for objects.

Overloaded the new and delete operators provides an easy way to integrate a mechanism similar to garbage collection capabilities (such as in Java), as we will shorty see later in this course.

By adding exception handling capabilities into new and delete, the code can be made more robust.

It is very easy to add customized behavior, such as overwriting deallocated memory with zeros in order to increase the security of critical application data.
