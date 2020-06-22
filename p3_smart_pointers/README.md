# Smart Pointers

### Common Problems with New and Delete

1. Proper pairing of new and delete : Every dynamically allocated object that is created with new must be followed by a manual deallocation at a "proper" place in the program. If the programer forgets to call delete (which can happen very quickly) or if it is done at an "inappropriate" position, memory leaks will occur which might clog up a large portion of memory.

2. Correct operator pairing : C++ offers a variety of new/delete operators, especially when dealing with arrays on the heap. A dynamically allocated array initialized with new[] may only be deleted with the operator delete[]. If the wrong operator is used, program behavior will be undefined - which is to be avoided at all cost in C++.

3. Memory ownership : If a third-party function returns a pointer to a data structure, the only way of knowing who will be responsible for resource deallocation is by looking into either the code or the documentation. If both are not available (as is often the case), there is no way to infer the ownership from the return type. As an example, in the final project of this course, we will use the graphical library wxWidgets to create the user interface of a chatbot application. In wxWidgets, the programmer can create child windows and control elements on the heap using new, but the framework will take care of deletion altogether. If for some reason the programmer does not know this, he or she might call delete and thus interfere with the inner workings of the wxWidgets library.

#### Benefits of Smart Pointers

To put it briefly: Smart pointers were introduced in C++ to solve the above mentioned problems by providing a degree of automatic memory management: When a smart pointer is no longer needed (which is the case as soon as it goes out of scope), the memory to which it points is automatically deallocated. When contrasted with smart pointers, the conventional pointers we have seen so far are often termed "raw pointers".

In essence, smart pointers are classes that are wrapped around raw pointers. By overloading the -> and * operators, smart pointer objects make sure that the memory to which their internal raw pointer refers to is properly deallocated. This makes it possible to use smart pointers with the same syntax as raw pointers. As soon as a smart pointer goes out of scope, its destructor is called and the block of memory to which the internal raw pointer refers is properly deallocated. 

This technique of wrapping a management class around a resource has been conceived by Bjarne Stroustroup and is called Resource Acquisition Is Initialization (RAII). Before we continue with smart pointers and their usage let us take a close look at this powerful concept.

#### Resource Acquisition is Initialization

In most programs of reasonable size, there will be many situations where a certain action at some point will necessitate a proper reaction at another point, such as:

1. Allocating memory with new or malloc, which must be matched with a call to delete or free.

2. Opening a file or network connection, which must be closed again after the content has been read or written.

3. Protecting synchronization primitives such as atomic operations, memory barriers, monitors or critical sections, which must be released to allow other threads to obtain them.

The general pattern of programming is to obtain the resource, use the resource, and then release the resource.

However, there are problems with this pattern:

1. The program may hit an exception during use and then proper release is never reached
2. There may be multiple points where a program could be released, making it difficult for us to keep track of all eventualities
3. We might simply forget to release the resource

So RAII to the rescue:
- major idea revolves around ownership and information hiding
- allocation and deallocation are hidden in the class definitions, so that when we use a class, we do not have to worry about allocation and releasing
- in other words, allocation and de-allocation should disappear from the surface level of the code
- Advantages:
    - Use class destructors to perform resource clean-up tasks such as proper memory deallocation when the RAII object gets out of scope
    - Manage ownership and lifetime of dynamically allocated objects
    - Implement encapsulation and information hiding due to resource acquisition and release being performed within the same object.

### RAII Example

```c++
int main()
{
    double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (size_t i = 0; i < 5; ++i)
    {
        // allocate the resource on the heap
        double *en = new double(i);

        // use the resource
        std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;

        // deallocate the resource
        delete en;
    }

    return 0;
}
```

At the beginning of the program, an array of double values den is allocated on the stack. Within the loop, a new double is created on the heap using new. Then, the result of a division is printed to the console. At the end of the loop, delete is called to properly deallocate the heap memory to which en is pointing. Even though this code is working as it is supposed to, it is very easy to forget to call delete at the end. Let us therefore use the principles of RAII to create a management class that calls delete automatically:

```c++
class MyInt
{
    int *_p; // pointer to heap data
public:
    MyInt(int *p = NULL) { _p = p; }
    ~MyInt() 
    { 
        std::cout << "resource " << *_p << " deallocated" << std::endl;
        delete _p; 
    }
    int &operator*() { return *_p; } // // overload dereferencing operator
};
```

In this example, the constructor of class MyInt takes a pointer to a memory resource. When the destructor of a MyInt object is called, the resource is deleted from memory - which makes MyInt an RAII memory management class. Also, the * operator is overloaded which enables us to dereference MyInt objects in the same manner as with raw pointers. Let us therefore slightly alter our code example from above to see how we can properly use this new construct:

```c++
int main()
{
    double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (size_t I = 0; I < 5; ++i)
    {
        // allocate the resource on the stack
        MyInt en(new int(i));

        // use the resource
        std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;
    }

    return 0;
}
```


The part `new int(i)` creates a new block of memory on the heap and initializes it with the value of i. The returned result is the address of the block of memory.

The part `MyInt en(…)` calls the constructor of class MyInt, passing the address of a valid memory block as a parameter.

After creating an object of class MyInt on the stack, which, internally, created an integer on the heap, we can use the dereference operator in the same manner as before to retrieve the value to which the internal raw pointer is pointing. Because the MyInt object en lives on the stack, it is automatically deallocated after each loop cycle - which automatically calls the destructor to release the heap memory.

We have thus successfully used the RAII idiom to create a memory management class that spares us from thinking about calling delete. By creating the MyInt object on the stack, we ensure that the deallocation occurs as soon as the object goes out of scope.

If we were to also declare the `MyInt` object on the heap each time, it would never get deallocated within the scope of each loop, hence creating a memory leak because it would not be destroyed when exiting the scope and thus the destructor method of `MyInt` would never get called



### Smart Pointers in Detail

This is similar to garbage collection in Java

The point is so that the programmer doesn't have to keep track of the places for proper memory deallocation

Pointer types:
1. Unique pointer - gives exclusive ownership, there must not be a second pointer to the same resource
2. Share pointer - multiple ownership (each will increase an internal reference counter), last one to stop using it will delete (when counter reaches 0)
3. Weak pointer - behaves similar to a shared pointer but does not increase reference count


Overview:
- smart pointers came to being with c++11
- help create programs that are memory leak free and exception safe



#### Unique Pointer

A unique pointer is the exclusive owner of the memory resource it represents. There must not be a second unique pointer to the same memory resource, otherwise there will be a compiler error. As soon as the unique pointer goes out of scope, the memory resource is deallocated again. Unique pointers are useful when working with a temporary heap resource that is no longer needed once it goes out of scope.

Example:

```c++
#include <memory>

void RawPointer()
{
    int *raw = new int; // create a raw pointer on the heap
    *raw = 1; // assign a value
    delete raw; // delete the resource again
}

void UniquePointer()
{
    std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
    *unique = 2; // assign a value
    // delete is not neccessary
}
```


A unique pointer is constructed using the following syntax:

`std::unique_ptr<Type> p(new Type);`


The function RawPointer contains the familiar steps of (1) allocating memory on the heap with new and storing the address in a pointer variable, (2) assigning a value to the memory block using the dereferencing operator * and (3) finally deleting the resource on the heap. As we already know, forgetting to call delete will result in a memory leak.

The function UniquePointer shows how to achieve the same goal using a smart pointer from the standard library. As can be seen, a smart pointer is a class template that is declared on the stack and then initialized by a raw pointer (returned by new ) to a heap-allocated object. The smart pointer is now responsible for deleting the memory that the raw pointer specifies - which happens as soon as the smart pointer goes out of scope. Note that smart pointers always need to be declared on the stack, otherwise the scoping mechanism would not work.

The smart pointer destructor contains the call to delete, and because the smart pointer is declared on the stack, its destructor is invoked when the smart pointer goes out of scope, even if an exception is thrown.


Unique pointer example:
```c++
#include <iostream>
#include <memory>
#include <string>

class MyClass
{
private:
    std::string _text;

public:
    MyClass() {}
    MyClass(std::string text) { _text = text; }
    ~MyClass() { std::cout << _text << " destroyed" << std::endl; }
    void setText(std::string text) { _text = text; }
};

int main()
{
    // create unique pointer to proprietary class
    std::unique_ptr<MyClass> myClass1(new MyClass());
    std::unique_ptr<MyClass> myClass2(new MyClass("String 2"));

    // call member function using ->
    myClass1->setText("String 1");

    // use the dereference operator * 
    *myClass1 = *myClass2;

    // use the .get() function to retrieve a raw pointer to the object
    std::cout << "Objects have stack addresses " << myClass1.get() << " and " << myClass2.get() << std::endl;

    return 0;
}
```

In the example now, we will construct a unique pointer to a custom class. Also, we will see how the standard -> and * operators can be used to access member functions of the managed object, just as we would with a raw pointer:

Note that the custom class MyClass has two constructors, one without arguments and one with a string to be passed, which initializes a member variable _text that lives on the stack. Also, once an object of this class gets destroyed, a message to the console is printed, along with the value of _text. In main, two unique pointers are created with the address of a MyClass object on the heap as arguments. With myClass2, we can see that constructor arguments can be passed just as we would with raw pointers. After both pointers have been created, we can use the -> operator to access members of the class, such as calling the function setText. From looking at the function call alone you would not be able to tell that myClass1 is in fact a smart pointer. Also, we can use the dereference operator * to access the value of myClass1 and myClass2 and assign the one to the other. Finally, the . operator gives us access to proprietary functions of the smart pointer, such as retrieving the internal raw pointer with get().

Summing up, the unique pointer allows a single owner of the underlying internal raw pointer. Unique pointers should be the default choice unless you know for certain that sharing is required at a later stage. We have already seen how to transfer ownership of a resource using the Rule of Five and move semantics. Internally, the unique pointer uses this very concept along with RAII to encapsulate a resource (the raw pointer) and transfer it between pointer objects when either the move assignment operator or the move constructor are called. Also, a key feature of a unique pointer, which makes it so well-suited as a return type for many functions, is the possibility to convert it to a shared pointer. 

#### Shared Pointer

Just as the unique pointer, a shared pointer owns the resource it points to. The main difference between the two smart pointers is that shared pointers keep a reference counter on how many of them point to the same memory resource. Each time a shared pointer goes out of scope, the counter is decreased. When it reaches zero (i.e. when the last shared pointer to the resource is about to vanish). the memory is properly deallocated. This smart pointer type is useful for cases where you require access to a memory location on the heap in multiple parts of your program and you want to make sure that whoever owns a shared pointer to the memory can rely on the fact that it will be accessible throughout the lifetime of that pointer.


```c++
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> shared1(new int);
    std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

    {
        std::shared_ptr<int> shared2 = shared1;
        std::cout << "shared pointer count = " << shared1.use_count() << std::endl;
    }
    
    std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

    return 0;
}
```

We can see that shared pointers are constructed just as unique pointers are. Also, we can access the internal reference count by using the method use_count(). In the inner block, a second shared pointer shared2 is created and shared1 is assigned to it. In the copy constructor, the internal resource pointer is copied to shared2 and the resource counter is incremented in both shared1 and shared2.

The lifetime of shared2 is limited to the scope denoted by the enclosing curly brackets. Thus, once this scope is left and shared2 is destroyed, the reference counter in shared1 is decremented by one


A shared pointer can also be redirected by using the reset() function. If the resource which a shared pointer manages is no longer needed in the current scope, the pointer can be reset to manage a different resource


Despite all the advantages of shared pointers, it is still possible to have problems with memory management though. Consider this scenario:

```c++
#include <iostream>
#include <memory>

class MyClass
{
public:
    std::shared_ptr<MyClass> _member;
    ~MyClass() { std::cout << "Destructor of MyClass called" << std::endl; }
};

int main()
{
    std::shared_ptr<MyClass> myClass1(new MyClass);
    std::shared_ptr<MyClass> myClass2(new MyClass);

    return 0;
}
```

The problem arises when we have circular references:
```
myClass1->_member = myClass2;
myClass2->_member = myClass1;
```

When myClass1 goes out of scope at the end of main, its destructor can’t clean up memory as there is still a reference count of 1 in the smart pointer, which is caused by the shared pointer _member in myClass2. The same holds true for myClass2, which can not be properly deleted as there is still a shared pointer to it in myClass1. This deadlock situation prevents the destructors from being called and causes a memory leak. When we use Valgrind on this program, we get the following summary:

```
==20360== LEAK SUMMARY:
==20360==    definitely lost: 16 bytes in 1 blocks
==20360==    indirectly lost: 80 bytes in 3 blocks
==20360==      possibly lost: 72 bytes in 3 blocks
==20360==    still reachable: 200 bytes in 6 blocks
==20360==         suppressed: 18,985 bytes in 160 blocks
```

As can be seen, the memory leak is clearly visible with 16 bytes being marked as "definitely lost". To prevent such circular references, there is a third smart pointer


#### Weak Pointers

Similar to shared pointers, there can be multiple weak pointers to the same resource. The main difference though is that weak pointers do not increase the reference count. Weak pointers hold a non-owning reference to an object that is managed by another shared pointer.

The following rule applies to weak pointers: You can only create weak pointers out of shared pointers or out of another weak pointer.

```c++
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> mySharedPtr(new int);
    std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

    std::weak_ptr<int> myWeakPtr1(mySharedPtr);
    std::weak_ptr<int> myWeakPtr2(myWeakPtr1);
    std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

    // std::weak_ptr<int> myWeakPtr3(new int); // COMPILE ERROR

    return 0;
}
```

First, a shared pointer to an integer is created with a reference count of 1 after creation. Then, two weak pointers to the integer resource are created, the first directly from the shared pointer and the second indirectly from the first weak pointer. As can be seen from the output, neither of both weak pointers increased the reference count. At the end of main, the attempt to directly create a weak pointer to an integer resource would lead to a compile error.


As we have seen with raw pointers, you can never be sure wether the memory resource to which the pointer refers is still valid. With a weak pointer, even though this type does not prevent an object from being deleted, the validity of its resource can be checked with the `expired()` function:

```c++
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> mySharedPtr(new int);
    std::weak_ptr<int> myWeakPtr(mySharedPtr);

    mySharedPtr.reset(new int);

    if (myWeakPtr.expired() == true)
    {
        std::cout << "Weak pointer expired!" << std::endl;
    }

    return 0;
}
```

Thus, with smart pointers, there will always be a managing instance which is responsible for the proper allocation and deallocation of a resource. In some cases it might be necessary to convert from one smart pointer type to another. Let us take a look at the set of possible conversions in the following.

#### Convering between smart pointers

```c++
#include <iostream>
#include <memory>

int main()
{
    // construct a unique pointer
    std::unique_ptr<int> uniquePtr(new int);
    
    // (1) shared pointer from unique pointer
    std::shared_ptr<int> sharedPtr1 = std::move(uniquePtr);

    // (2) shared pointer from weak pointer
    std::weak_ptr<int> weakPtr(sharedPtr1);
    std::shared_ptr<int> sharedPtr2 = weakPtr.lock();

    // (3) raw pointer from shared (or unique) pointer   
    int *rawPtr = sharedPtr2.get();
    delete rawPtr;

    return 0;
}
```

In (1), a conversion from unique pointer to shared pointer is performed. You can see that this can be achieved by using std::move, which calls the move assignment operator on sharedPtr1 and steals the resource from uniquePtr while at the same time invalidating its resource handle on the heap-allocated integer.

In (2), you can see how to convert from weak to shared pointer. Imagine that you have been passed a weak pointer to a memory object which you want to work on. To avoid invalid memory access, you want to make sure that the object will not be deallocated before your work on it has been finished. To do this, you can convert a weak pointer to a shared pointer by calling the lock() function on the weak pointer.

In (3), a raw pointer is extracted from a shared pointer. However, this operation does not decrease the reference count within sharedPtr2. This means that calling delete on rawPtr in the last line before main returns will generate a runtime error as a resource is trying to be deleted which is managed by sharedPtr2 and has already been removed. The output of the program when compiled with g++ thus is: malloc: *** error for object 0x1003001f0: pointer being freed was not allocated.

Note that there are no options for converting away from a shared pointer. Once you have created a shared pointer, you must stick to it (or a copy of it) for the remainder of your program.


#### Some Guidelines from C++ core

1. R. 10: Avoid malloc and free While the calls (MyClass*)malloc( sizeof(MyClass) ) and new MyClass both allocate a block of memory on the heap in a perfectly valid manner, only new will also call the constructor of the class and free the destructor. To reduce the risk of undefined behavior, malloc and free should thus be avoided.

2. R. 11: Avoid calling new and delete explicitly Programmers have to make sure that every call of new is paired with the appropriate delete at the correct position so that no memory leak or invalid memory access occur. The emphasis here lies in the word "explicitly" as opposed to implicitly, such as with smart pointers or containers in the standard template library.

3. R. 12: Immediately give the result of an explicit resource allocation to a manager object It is recommended to make use of manager objects for controlling resources such as files, memory or network connections to mitigate the risk of memory leaks. This is the core idea of smart pointers as discussed at length in this section.


If we must use new and delete:

- A call to new should not be located too far away from the corresponding delete. It is bad style to stretch you new / delete pairs throughout your program with references criss-crossing your entire code.

- Calls to new and delete should always be hidden from third parties so that they must not concern themselves with managing memory manually (which is similar to R. 12).


#### More specific guidelines on smart pointers

In addition to the above recommendations, the C++ core guidelines also contain a total of 13 rules for the recommended use of smart pointers. In the following, we will discuss a selection of these:

R. 20 : Use unique_ptr or shared_ptr to represent ownership

R. 21 : Prefer unique_ptr over std::shared_ptr unless you need to share ownership

Both pointer types express ownership and responsibilities (R. 20). A unique_ptr is an exclusive owner of the managed resource; therefore, it cannot be copied, only moved. In contrast, a shared_ptr shares the managed resource with others. As described above, this mechanism works by incrementing and decrementing a common reference counter. The resulting administration overhead makes shared_ptr more expensive than unique_ptr. For this reason unique_ptr should always be the first choice (R. 21).

R. 22 : Use make_shared() to make shared_ptr

R. 23 : Use make_unique() to make std::unique_ptr

The increased management overhead compared to raw pointers becomes in particular true if a shared_ptr is used. Creating a shared_ptr requires (1) the allocation of the resource using new and (2) the allocation and management of the reference counter. Using the factory function make_shared is a one-step operation with lower overhead and should thus always be preferred. (R.22). This also holds for unique_ptr (R.23), although the performance gain in this case is minimal (if existent at all).

But there is an additional reason for using the make_... factory functions: Creating a smart pointer in a single step removes the risk of a memory leak. Imagine a scenario where an exception happens in the constructor of the resource. In such a case, the object would not be handled properly and its destructor would never be called - even if the managing object goes out of scope. Therefore, make_shared and make_unique should always be preferred. Note that make_unique is only available with compilers that support at least the C++14 standard.

R. 24 : Use weak_ptr to break cycles of shared_ptr
We have seen that weak pointers provide a way to break a deadlock caused by two owning references which are cyclicly referring to each other. With weak pointers, a resource can be safely deallocated as the reference counter is not increased.

The remaining set of guideline rules referring to smart pointers are mostly concerning the question of how to pass a smart pointer to a function.
