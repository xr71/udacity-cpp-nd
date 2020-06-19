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


